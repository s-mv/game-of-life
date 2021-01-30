document.querySelector(".button").onclick = () => {
  window.open(`./web/main.html?-d ${document.querySelector("#x").value || 20
    } ${document.querySelector("#y").value || 20
    } -r ${document.querySelector("#rules").value 
    } ;`, "smv");
}