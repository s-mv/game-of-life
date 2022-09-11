import './style.scss';
import init from './.tmp/lib.wasm?init';

let array = new Int8Array();
let rule;

let runGameAlgorithm, memory, updateRules, acceptArray;

let width = 100;
let height = 100; // this is going to change any way
let size; // per cell

// DOM and stuff
let ruleWindow;
let input;
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
  let x = x_mouse / size;
  let y = y_mouse / size;
  array[~~y * width + ~~x] = val;
}

let drawLine = (x1, y1, x2, y2) => {
  ctx.beginPath();
  ctx.moveTo(x1, y1);
  ctx.lineTo(x2, y2);
  ctx.stroke();
};

// let ruleMaker = (rules) => {
//   let ret = [];
//   // for (let i = 0; i < rules.length; i++) {
//   // }
//   return new Int8Array(ret);
// }

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
  } else if (time.tick >= 600) {
    runGameAlgorithm();
    array = new Int8Array(memory.buffer, acceptArray(width, height), width * height);
    time.tick = 0;
  }
  ctx.fillStyle = cellColour;
  ctx.strokeStyle = gridColour;
  // render
  ctx.clearRect(0, 0, window.innerWidth, window.innerHeight);
  // draw a grid first
  for (let i = 0; i < width; i++) {
    drawLine(i * size, 0, i * size, window.innerHeight);
  }
  for (let i = 0; i < height; i++) {
    drawLine(0, i * size, window.innerWidth, i * size);
  }

  for (let i = 0; i < array.length; i++) {
    let val = array[i];
    let x = (i % width) * size;
    let y = ~~(i / width) * size;
    if (val) ctx.fillRect(x, y, size, size);
  }
}

init({
  env: {
    consoleLog: console.log,
  }
}).then((instance) => {
  // set up width and height
  size = (window.innerWidth > window.innerHeight) ? window.innerWidth / width : window.innerHeight / height;
  // fill the whole screen
  if (window.innerWidth < window.innerHeight) width = 1 + ~~(window.innerWidth / size);
  else height = 1 + ~~(window.innerHeight / size);

  // get all the functions and memory buffer from in there
  acceptArray = instance.exports.acceptArray;
  updateRules = instance.exports.updateRules;
  memory = instance.exports.memory;
  runGameAlgorithm = instance.exports.runGameAlgorithm;

  // accept array from WASM
  array = new Int8Array(memory.buffer, acceptArray(width, height), width * height);

  offset += width * height * Int8Array.BYTES_PER_ELEMENT;
  offset += 4 * Int32Array.BYTES_PER_ELEMENT;

  // export rule array to WASM
  rule = "l2=0 m3=0 =3=1";
  let rule_arr = new Int8Array(memory.buffer, offset, rule.length);
  rule_arr.set(new TextEncoder().encode(rule));
  updateRules(offset, rule_arr.length);

  // offset += rule_arr.length * Int8Array.BYTES_PER_ELEMENT;

  // set up DOM variables
  ruleWindow = document.querySelector("#rules");
  pausedText = document.querySelector("#paused");
  input = document.querySelector("input");

  ctx = document.querySelector("#canvas").getContext("2d");
  ctx.canvas.width = window.innerWidth;
  ctx.canvas.height = window.innerHeight;

  // TODO scroll to increase/decrease number of rows
  // is this even needed
  window.onscroll = (e) => { }

  window.onkeydown = (e) => {
    document.querySelector("#notes").classList.add("hidden");

    if (e.key == "Shift") ruleWindow.classList.toggle("hidden");
    if (!ruleWindow.classList.contains("hidden")) input.focus();
    if (e.key == " ") {
      canEdit = true;
      pausedText.classList.remove("hidden");
    }
    if (e.key == "x") mouse.delete = true;
  }

  window.onkeyup = (e) => {
    if (e.key == " ") {
      canEdit = false;
      pausedText.classList.add("hidden");
    }
    if (e.key == "x") mouse.delete = false;
  }

  ruleWindow.onkeydown = (e) => {
    // e.preventDefault();
    if (e.code != "Enter" && e.key != "Escape")
      return;

    ruleWindow.classList.add("hidden");
    let rules = new Int8Array(memory.buffer, offset, input.value.length ? input.value.length : "l2=0 m3=0 =3=1".length);

    rules.set(new TextEncoder().encode(input.value || "l2=0 m3=0 =3=1"));
    updateRules(rules, rules.length);
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