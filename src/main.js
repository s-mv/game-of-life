import './style.scss';
import init from './.tmp/lib.wasm?init';

let array;
let runGameAlgorithm;

let width = 100;
let height = 100; // this is going to change any way
let size; // per cell

// DOM and stuff
let ruleWindow;
let pausedText;
let ctx;

let mouse = { x: 0, y: 0, down: false, delete: false };
let time = { now: 0, last: 0, tick: 0 }

let cellColour = "#8f00ff";
let gridColour = "#444444";

let canEdit = false;

// [<------cell array------>:<-rules->:---]
// offset for storing rules ^ this point
let offset; // idk why this is global

let getCell = (x, y) => array[y * width + x];
// set cell at position
let setCellPos = (x_mouse, y_mouse, val) => {
  let x = x_mouse * width / window.innerWidth;
  let y = y_mouse / size;
  array[~~y * width + ~~x] = val;
}

let drawLine = (x1, y1, x2, y2) => {
  ctx.beginPath();
  ctx.moveTo(x1, y1);
  ctx.lineTo(x2, y2);
  ctx.stroke();
};

let loopFn = () => {
  // tick
  time.now = new Date().getTime();
  let diff = time.now - time.then;
  time.then = time.now;
  time.tick += diff;

  // render
  if (canEdit) {
    if (mouse.down) {
      setCellPos(mouse.x, mouse.y, !mouse.delete);
    }
  } else if (time.tick >= 400) {
    runGameAlgorithm();
    time.tick = 0;
  }
  ctx.fillStyle = cellColour;
  ctx.strokeStyle = gridColour;
  // render
  ctx.clearRect(0, 0, window.innerWidth, window.innerHeight);
  // draw a grid first
  {
    for (let i = 0; i < width; i++) {
      drawLine(i * size, 0, i * size, window.innerHeight);
    }
    for (let i = 0; i < height; i++) {
      drawLine(0, i * size, window.innerWidth, i * size);
    }
  }

  for (let i = 0; i < array.length; i++) {
    let val = array[i];
    let x = (i % width) * size;
    let y = ~~(i / width) * size;
    if (val) ctx.fillRect(x, y, size, size);
  }
}

init().then((instance) => {
  // get all the functions and memory buffer from in there
  let { acceptArray, updateRules, memory } = instance.exports;
  runGameAlgorithm = instance.exports.runGameAlgorithm;

  // export array to WASM
  array = new Int8Array(memory.buffer, 0, width * height).fill(0);
  offset = width * height * Int8Array.BYTES_PER_ELEMENT;
  acceptArray(array.byteOffset, array.length);

  // set up DOM variables
  ruleWindow = document.querySelector("#rules");
  pausedText = document.querySelector("#paused");

  ctx = document.querySelector("#canvas").getContext("2d");
  ctx.canvas.width = window.innerWidth;
  ctx.canvas.height = window.innerHeight;

  // set up width and height
  size = window.innerWidth / width;
  // fill the whole screen
  height = 1 + window.innerHeight / size;

  // TODO scroll to increase/decrease number of rows
  // is this even needed
  window.onscroll = (e) => { }

  window.onkeydown = (e) => {
    if (e.key == "Shift") ruleWindow.hidden = !ruleWindow.hidden;
    if (e.key == " ") {
      canEdit = true;
      pausedText.hidden = false;
    }
    if (e.key == "x") mouse.delete = true;
  }

  window.onkeyup = (e) => {
    if (e.key == " ") {
      canEdit = false;
      pausedText.hidden = true;
    }
    if (e.key == "x") mouse.delete = false;
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

  // and finally
  time.now = new Date().getTime();
  time.then = time.now - 1 / 60;
  setInterval(loopFn, 60);
});