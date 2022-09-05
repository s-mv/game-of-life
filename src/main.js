import './style.scss';
import init from './.tmp/lib.wasm?init';

let width = 100;
let height = 100;
let rows, columns;

let ruleWindow;
let ctx;

let mouse = { x: 0, y: 0, down: false, delete: false };

let cellColour = "#8f00ff";

let canEdit = false;

// [<------cell array------>:<-rules->:---]
// offset for storing rules ^ this point
let offset;


let loopFn = () => {
  if(canEdit) {
    
  } else runGameAlgorithm();
  // render
 }

init().then((instance) => {
  // get all the functions and memory buffer from in there
  const { acceptArray, runGameAlgorithm, getCell, setCell, updateRules, memory } = instance.exports;

  // init and then export array to WASM
  let array;
  array = new Int8Array(memory.buffer, 0, width * height).fill(0);
  offset = width * height * Int8Array.BYTES_PER_ELEMENT;
  acceptArray(array.byteOffset, array.length);

  // set up DOM variables
  ctx = document.querySelector("#canvas").getContext("2d");
  ruleWindow = document.querySelector("#rules");

  // TODO scroll to increase/decrease number of rows
  // is this even needed
  window.onscroll = (e) => { }

  window.onkeydown = (e) => {
    if (e.key == "Shift") ruleWindow.hidden = !ruleWindow.hidden;
    if(e.key == "Space") canEdit = true;
  }

  window.onkeyup = (e) => {
    if(e.key == "Space") canEdit = false;
  }

  ruleWindow.onkeydown = (e) => {
    if (e.code != "EnterKey") return;

    let rules = new Int8Array(memory.buffer, offset, e.value.length);
    rules.set(e.value.split(""));
    updateRules(rules);
  }

  window.onmousedown = window.onmouseup = (e) => {
    mouse.down = e.type == "mousedown";

  }

  window.onmousemove = (e) => {
    mouse.x = e.clientX;
    mouse.y = e.clientY;
  }
});

