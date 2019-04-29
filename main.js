var actionitem = ['brown','green','nonarea','water'];
var npcs = ['grunt', 'ex', 'eye', 'key'];
var items = ['stick','normal','raj','john','lance','shield_1', 'shield_2','light', 'health'];
var lastClicked;
var currentClass;
var map = createArray(36,36);
var extra_list = new Map();
var radius = 1;

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
            var classlist = el.classList;
            var canBreak;
            for(var i=0; i < classlist.length; i++){
                canBreak = npcs.find(function(element){return element == classlist[i]});
                if(canBreak){
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

            console.log(canBreak + " " + currentClass);
            if(canBreak == currentClass){
                el.classList.remove(currentClass);
                var coor_string = col.toString() + "," + row.toString();
                extra_list.delete(coor_string);
            }
            else{       
                el.classList.add(currentClass);
                var coor_string = col.toString() + "," + row.toString();
                var new_item = {type: 0, x: 0, y: 0};
                new_item.type = determineID(currentClass);
                new_item.x = row;
                new_item.y = col;
                extra_list.set(coor_string,new_item);
            }
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
    if(itemindex != -1)
        fillInMap(row,col,itemindex);
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

function fillInMap(row,col,itemindex){
    var tmprad = radius-1;
    if(tmprad == 0){
        map[row][col] = itemindex;
        console.log("hit");
    }
    else{
        console.log("size: "+tmprad);
        var box = [];
        var width = (2*tmprad)+1;
        for(var i=-1*tmprad; i <= tmprad; i++){
            for(var j=-1*tmprad; j <= tmprad; j++){
                var coordinate = {x:i,y:j};
                box.push(coordinate);
            }
        }
        console.log(box);
        console.log(col);
        //after generating box, assign values to map
        for(var i=0; i < box.length; i++){
            //if(box[i].x + parseInt(col) >= 0 && box[i].y + parseInt(row) >= 0 && box[i].x + parseInt(col) < 36 && box[i].y + parseInt(row) < 36){
            if(box[i].x + col >= 0 && box[i].y + row >= 0 && box[i].x + col < 36 && box[i].y + row < 36){
                map[box[i].y+row][box[i].x+col] = itemindex;
            }
        }

        //render it (slowish):
        var grid = document.getElementsByClassName('grid')[0];
        for(var i=0; i < grid.childNodes.length; i++){
            var tmp = grid.childNodes[i].childNodes;
            for(var j=0; j < tmp.length; j++){
                //remove old terrain:
                for(var x = 0; x < actionitem.length; x++){
                    if(tmp[j].classList.length == 0)
                        break;
                    else{
                        tmp[j].classList.remove(actionitem[x]);
                    }
                }
                tmp[j].classList.add(actionitem[map[i][j]]);
            }
        }
        console.log(map);
    }
}   

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

function import_file(data){
    console.log("Getting data from items...");
    var split_data = data.split('\r\n');
    if(split_data.length == 1){
        split_data = data.split('\n');
    }
    var trav_i = 0; 
    while(split_data[trav_i] != '-1'){trav_i++;};
    trav_i++;

    var size_total = split_data[trav_i].split(" ");
    var size_y = parseInt(size_total[0]);
    var size_x = parseInt(size_total[1]);
    
    trav_i++;
    var i = 0;
    console.log(split_data);
    //Get data for grid:
    while(split_data[trav_i] != "-1"){
        var split_row = split_data[trav_i].split(" ");
        for(var j=0; j < split_row.length; j++){
            //console.log("grid: "+i+", "+j);
            //console.log(split_row[j]);
            map[i][j] = parseInt(split_row[j]);
        }
        trav_i++;
        i++;
    }

    trav_i++;
    var two_times = 0;
    //Get data from items:
    //clear old items:
    extra_list.clear();
    while(two_times < 2){
        if(split_data[trav_i] == "-1")
            two_times++;
        else{
            var split_row = split_data[trav_i].split(" ");
            
            //add to extralist:
            //for(var i=0; i < split_row.length; i++){
                var combined_key = split_row[1]+","+split_row[2];
                var tmp;
                if(two_times == 0)
                    tmp = {type: parseInt(split_row[0])+4, x: parseInt(split_row[2]), y: parseInt(split_row[1])};
                else
                    tmp = {type: parseInt(split_row[0]), x: parseInt(split_row[2]), y: parseInt(split_row[1])};
                extra_list.set(combined_key,tmp);
            //}
        }
        trav_i++;
    }
    console.log(map);
    console.log(extra_list);
}

function force_redraw(){
    var grid = document.getElementsByClassName("grid")[0];

    for(var i=0; i < grid.childNodes.length; i++){
        var tmp = grid.childNodes[i].childNodes;
        for(var j=0; j < tmp.length; j++){
            //remove old terrain:
            for(var x = 0; x < actionitem.length; x++){
                if(tmp[j].classList.length == 0)
                    break;
                else{
                    tmp[j].classList.remove(actionitem[x]);
                }
            }
            tmp[j].classList.add(actionitem[map[i][j]]);
            
            // remove all enemies
            for(var x = 0; x < npcs.length; x++){
                if(tmp[j].classList.length == 1)
                    break;
                else{
                    tmp[j].classList.remove(npcs[x]);
                }
            }
            
            // if there's still something, then it must be items, remove that:
            if(tmp[j].classList.length != 1){
                for(var x = 0; x < items.length; x++){
                    if(tmp[j].classList.length == 1)
                        break;
                    else{
                        tmp[j].classList.remove(npcs[x]);
                    }
                }
            }

            //add the extra stuff: 
            for(var x of extra_list.values()){
                if(x.x ==i && x.y == j){
                    //draw it:
                    if(x.type < 4){
                        tmp[j].classList.add(npcs[x.type]);
                    }
                    else{
                        tmp[j].classList.add(items[x.type-4]);
                    }   
                }
            }
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
var increment = document.getElementById('brush');

grid_parent.appendChild(terrain);
grid_parent.appendChild(enemy);
grid_parent.appendChild(item_bar);
grid_parent.appendChild(grid);
document.getElementById("exportme").addEventListener("click", function(){
    var filename = "export_map.txt";
    download(filename);
}, false);

document.getElementById('file-input').addEventListener('change', readSingleFile, false);
increment.addEventListener('change', function(){radius = increment.value}, false)