document.getElementById('canvas').getContext("2d").imageSmoothingEnabled = false;


document.querySelector(".button").onclick = () => {
  document.querySelector(".container").classList.remove("hidden");

  Module({
    canvas: document.getElementById('canvas'),
    arguments: [
      document.querySelector("#x").value || 20,
      document.querySelector("#y").value || 20,
      ...document.querySelector("#rules").value.split(/ /gi)
    ],
  });
}