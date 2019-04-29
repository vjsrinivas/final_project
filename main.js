var actionitem = ['brown','green','nonarea','water'];
var npcs = ['grunt', 'ex', 'eye', 'key'];
var items = ['shield_1', 'shield_2', 'stick', 'normal', 'raj', 'lance', 'john','light', 'health'];
var lastClicked;
var currentClass;
var map = createArray(36,36);
var extra_list = new Map();
initMap();

var grid = clickableGrid(36,36,function(el,row,col,i){
    console.log("You clicked on element:",el);
    console.log("You clicked on row:",row);
    console.log("You clicked on col:",col);
    console.log("You clicked on item #:",i);

    if(currentClass){
        var isFromTerrain = actionitem.find(function(element){return element == currentClass});
        if(!isFromTerrain){
            //no need to search for items because they need to replace each other anyways:
            var isEnemy = 0;
            var classlist = el.classList;
            var canBreak;
            for(var i=0; i < classlist.length; i++){
                canBreak = npcs.find(function(element){return element == classlist[i]});
                if(canBreak){
                    isEnemy = 1;
                    break;
                }
            }
            
            if(!canBreak){
                //search through items array:
                for(var i=0; i < classlist.length; i++){
                    canBreak = items.find(function(element){return element == classlist[i]});
                    if(canBreak)
                        break;
                }
            }

            if(canBreak)
                el.classList.remove(canBreak);
            el.classList.add(currentClass);
            
            var coor_string = col.toString() + "," + row.toString();
            var new_item = {type: 0, x: 0, y: 0};
            new_item.type = determineID(currentClass);
            new_item.x = row;
            new_item.y = col;
            extra_list.set(coor_string,new_item);
        } 
        else{
            //knowing it's from terrain:
            //find which existing terrain should be removed and replaced by currentClass (new terrain)
            var classlist = el.classList;
            var canBreak;
            for(var i=0; i < classlist.length; i++){
                canBreak = actionitem.find(function(element){return element == classlist[i]});
                if(canBreak)
                    break;
            }

            el.classList.remove(canBreak);
            el.classList.add(currentClass);
        }
    }
    
    var itemindex =  actionitem.findIndex(function(element){return element == currentClass;});
    console.log(itemindex);
    if(itemindex != -1)
        map[row][col] = itemindex;
    console.log(map);
});

var terrain = clickableActionbar(actionitem, function(el){
    console.log("You click on element:",el)
    currentClass = el.className;
    console.log(currentClass);
    el.className +=' active';
    //console.log(lastClicked.className);
    if (lastClicked) lastClicked.className = lastClicked.className.slice(0,-7);
    //if (lastClicked) console.log(lastClicked.className);
    lastClicked = el;
});

var enemy = clickableActionbar(npcs, function(el){
    currentClass = el.className;
    el.className +=' active';
    //console.log(lastClicked.className);
    if (lastClicked) lastClicked.className = lastClicked.className.slice(0,-7);
    //if (lastClicked) console.log(lastClicked.className);
    lastClicked = el;
});

var item_bar = clickableActionbar(items, function(el){
    currentClass = el.className;
    el.className +=' active';
    //console.log(lastClicked.className);
    if (lastClicked) lastClicked.className = lastClicked.className.slice(0,-7);
    //if (lastClicked) console.log(lastClicked.className);
    lastClicked = el;
});

function clickableGrid( rows, cols, callback ){
    var i=0;
    var grid = document.createElement('table');
    grid.className = 'grid';
    for (var r=0;r<rows;++r){
        var tr = grid.appendChild(document.createElement('tr'));
        for (var c=0;c<cols;++c){
            var cell = tr.appendChild(document.createElement('td'));
            cell.className = "nonarea";
            if(c == 0 && r == 0)
                cell.className += " mc";
            cell.addEventListener('click',(function(el,r,c,i){
                return function(){
                    callback(el,r,c,i);
                }
            })(cell,r,c,i),false);
        }
    }
    return grid;
}

function clickableActionbar(item, callback){
    var grid = document.createElement('table');
    grid.className = 'grid_action';
    var tr = grid.appendChild(document.createElement('tr'));
    for(var i=0; i < item.length; i++){
        var cell = tr.appendChild(document.createElement('td'));
        cell.className=item[i];
        cell.addEventListener('click',(function(el){
            return function(){
                callback(el);
            }
        })(cell),false);
    }
    return grid;
}

function initMap(){
    for(var i=0; i < map.length; i++){
        for(var j=0; j < 36; j++){
            map[i][j] = 2;
        }
    }
}

// Taken from: https://bit.ly/2GEi9Pd
function createArray(length) {
    var arr = new Array(length || 2),
        i = length;

    if (arguments.length > 1) {
        var args = Array.prototype.slice.call(arguments, 1);
        while(i--) arr[length-1 - i] = createArray.apply(this, args);
    }

    return arr;
}

function download(filename){
    var str_output ='0 ./assets/dirt.png\r\n1 ./assets/grass.jpg\r\n2 ./assets/nonarea.jpg\r\n3 ./assets/water.jpg\r\n4 ./assets/dark.png\r\n-1\r\n36 36\r\n';
    
    //stringify entire map array
    for(var i=0; i < map.length; i++){
        for(var j=0; j < map[i].length; j++){
            if(j != map[i].length-1){
                str_output += map[i][j].toString() + ' ';
            }
            else
                str_output += map[i][j].toString();
        }
        str_output += '\r\n';
    }
    str_output +='-1\r\n';
    

    var enemy_list = [];
    if(extra_list.size != 0){
        for(const k of extra_list.values()){
            if(k.type >= 4){
                str_output += k.type-4 + " " + k.y + " " + k.x + "\r\n";
            }
            else{
               enemy_list.push(k);
            }
        }
    }
    str_output += '-1\r\n';

    if(enemy_list.length != 0){
        for(var i=0; i < enemy_list.length; i++){
            str_output += enemy_list[i].type + " " + enemy_list[i].y + " " + enemy_list[i].x + "\r\n";
        }
    }
    str_output += '-1\r\n';

    //console.log(str_output);
    
    // Taken from: https://bit.ly/2oKP2ll
    var downloadbtn = document.createElement('a');
    downloadbtn.setAttribute('href', 'data:text/plain;charset=utf-8,' + encodeURIComponent(str_output));
    downloadbtn.setAttribute('download', filename);
    downloadbtn.style.display = 'none';

    document.body.appendChild(downloadbtn);
    downloadbtn.click();
    document.body.removeChild(downloadbtn);
}

function determineID(id){
    switch(id){
        case "grunt":
            return 0;
        case "ex":
            return 1;
        case "eye":
            return 2;
        case "key":
            return 3;
        case "stick":
            return 4;
        case "normal":
            return 5;
        case "raj":
            return 6;
        case "john":
            return 7;
        case "lance":
            return 8;
        case "shield_1":
            return 9;
        case "shield_2":
            return 10;
        case "light":
            return 11;
        case "health":
            return 12;
        default:
            return -1;
    }
}

function determineTerrainID(id){
    if(id == 'brown')
        return 0;
    else if(id == 'green')
        return 1;
    else if(id == 'nonarea')
        return 2;
    else if(id == 'water')
        return 3;
    else
        return 2;
}

function import_file(data){
    var split_data = data.split('\r\n');
    var trav_i = 0; 
    while(split_data[trav_i] != '-1'){trav_i++;};
    trav_i++;

    var size_total = split_data[trav_i].split(" ");
    var size_y = parseInt(size_total[0]);
    var size_x = parseInt(size_total[1]);
    
    trav_i++;
    var i = 0;

    console.log(split_data);
    while(split_data[trav_i] != "-1"){
        var split_row = split_data[trav_i].split(" ");
        console.log(split_row);
        
        for(var j=0; j < split_row.length; j++){
            console.log("grid: "+i+", "+j);
            console.log(split_row[j]);
            map[i][j] = parseInt(split_row[j]);
        }
        trav_i++;
        i++;
    }
    console.log(map);
}

function force_redraw(){
    var grid = document.getElementsByClassName("grid")[0];
    
    for(var i=0; i < grid.childNodes.length; i++){
        var tmp = grid.childNodes[i].childNodes;
        for(var j=0; j < tmp.length; j++){
            //console.log(grid.childNodes[i]);
            tmp[j].classList.add();
        }
    }
}

// Taken from: http://researchhubs.com/post/computing/javascript/open-a-local-file-with-javascript.html
function readSingleFile(e) {
    var file = e.target.files[0];
    if (!file) {
      return;
    }
    var reader = new FileReader();
    reader.onload = function(e) {
      var contents = e.target.result;
      // Run reading here:
      import_file(contents);
      force_redraw();
    };
    reader.readAsText(file);
  }

var grid_parent = document.getElementById("grid_parent");
grid_parent.appendChild(terrain);
grid_parent.appendChild(enemy);
grid_parent.appendChild(item_bar);
grid_parent.appendChild(grid);
document.getElementById("exportme").addEventListener("click", function(){
    var filename = "export_map.txt";
    download(filename);
}, false);

document.getElementById('file-input').addEventListener('change', readSingleFile, false);