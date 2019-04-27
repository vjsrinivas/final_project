var position = {type: 0, x: 0, y: 0};
var actionitem = ['green','brown','water','nonarea'];
var npcs = ['grunt', 'ex', 'eye', 'key'];
var items = [''];
var lastClicked;
var currentClass;
var map = createArray(36,36);
var enemy_list = Array();
var item_list = Array();
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
                if(canBreak)
                    break;
            }
            
            if(!canBreak){
                //serach through items array:
            }

            el.classList.remove(canBreak);
            el.classList.add(currentClass);
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
    
    if(currentClass == 'brown')
        map[col][row] = 0;
    else if(currentClass == 'green')
        map[col][row] = 1;
    else if(currentClass == 'nonarea')
        map[col][row] = 2;
    else if(currentClass == 'water')
        map[col][row] = 3;
    else
        map[col][row] = 2;
    //if (lastClicked) lastClicked.className='';
    //lastClicked = el;
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
    var str_output ='0 ./assets/dirt.png\n1 ./assets/grass.jpg\n2 ./assets/nonarea.jpg\n3 ./assets/water.jpg\n4 ./assets/dark.png\n-1\n35 35';
    
    //stringify entire map array
    for(var i=0; i < map.length; i++){
        for(var j=0; j < map[i].length; j++){
            if(j != map[i].length-1){
                str_output += map[i][j].toString() + ' ';
            }
            else
            str_output += map[i][j].toString();
        }
        str_output += '\n';
    }
    str_output +='-1\n';
    
    if(enemy_list.length != 0){

    }
    str_output += '-1\n';

    if(item_list.length != 0){

    }
    str_output += '-1\n';

    console.log(str_output);
    
    var downloadbtn = document.createElement('a');
    downloadbtn.setAttribute('href', 'data:text/plain;charset=utf-8,' + encodeURIComponent(str_output));
    downloadbtn.setAttribute('download', filename);
    return downloadbtn;
}

var grid_parent = document.getElementById("grid_parent");
grid_parent.appendChild(terrain);
grid_parent.appendChild(enemy);
grid_parent.appendChild(grid);
grid_parent.appendChild(download("test.txt"));