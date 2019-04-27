var actionitem = ['green','brown','water','nonarea'];
var npcitems = ['grunt', 'excommunicator', 'eye', 'keyboy'];
var lastClicked;
var currentClass;
var map = createArray(36,36);
initMap();
console.log(map);

var grid = clickableGrid(36,36,function(el,row,col,i){
    console.log("You clicked on element:",el);
    console.log("You clicked on row:",row);
    console.log("You clicked on col:",col);
    console.log("You clicked on item #:",i);

    if(currentClass)
        el.className=currentClass;
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

var action = clickableActionbar(actionitem, function(el){
    console.log("You click on element:",el)
    currentClass = el.className;
    console.log(currentClass);
    el.className +=' active';
    //console.log(lastClicked.className);
    if (lastClicked) lastClicked.className = lastClicked.className.slice(0,-7);
    //if (lastClicked) console.log(lastClicked.className);
    lastClicked = el;
});

var grid_parent = document.getElementById("grid_parent");
grid_parent.appendChild(action);
grid_parent.appendChild(grid);
download("Test");

function clickableGrid( rows, cols, callback ){
    var i=0;
    var grid = document.createElement('table');
    grid.className = 'grid';
    for (var r=0;r<rows;++r){
        var tr = grid.appendChild(document.createElement('tr'));
        for (var c=0;c<cols;++c){
            var cell = tr.appendChild(document.createElement('td'));
            cell.className = "nonarea";

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

    console.log(str_output);
    //var downloadbtn = document.createElement('a');
    //downloadbtn.setAttribute('href', )
}