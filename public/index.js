(function(){const A=document.createElement("link").relList;if(A&&A.supports&&A.supports("modulepreload"))return;for(const t of document.querySelectorAll('link[rel="modulepreload"]'))o(t);new MutationObserver(t=>{for(const i of t)if(i.type==="childList")for(const I of i.addedNodes)I.tagName==="LINK"&&I.rel==="modulepreload"&&o(I)}).observe(document,{childList:!0,subtree:!0});function e(t){const i={};return t.integrity&&(i.integrity=t.integrity),t.referrerpolicy&&(i.referrerPolicy=t.referrerpolicy),t.crossorigin==="use-credentials"?i.credentials="include":t.crossorigin==="anonymous"?i.credentials="omit":i.credentials="same-origin",i}function o(t){if(t.ep)return;t.ep=!0;const i=e(t);fetch(t.href,i)}})();const G=async(n={},A)=>{let e;if(A.startsWith("data:")){const o=A.replace(/^data:.*?base64,/,"");let t;if(typeof Buffer=="function"&&typeof Buffer.from=="function")t=Buffer.from(o,"base64");else if(typeof atob=="function"){const i=atob(o);t=new Uint8Array(i.length);for(let I=0;I<i.length;I++)t[I]=i.charCodeAt(I)}else throw new Error("Failed to decode base64-encoded data URL, Buffer and atob are not supported");e=await WebAssembly.instantiate(t,n)}else{const o=await fetch(A),t=o.headers.get("Content-Type")||"";if("instantiateStreaming"in WebAssembly&&t.startsWith("application/wasm"))e=await WebAssembly.instantiateStreaming(o,n);else{const i=await o.arrayBuffer();e=await WebAssembly.instantiate(i,n)}}return e.instance},R=n=>G(n,"data:application/wasm;base64,AGFzbQEAAAABFQRgAABgAn9/AX9gA39/fwBgAn9/AAMIBwABAgMBAQAFAwEAAgZZDn8BQcCsBQt/AEGACAt/AEGECAt/AEGICAt/AEGQCAt/AEGg1gALfwBBoN4AC38AQbDeAAt/AEGACAt/AEHArAELfwBBgAgLfwBBwKwFC38AQQALfwBBAQsHjwIVBm1lbW9yeQIAEV9fd2FzbV9jYWxsX2N0b3JzAAALYWNjZXB0QXJyYXkAAQV3aWR0aAMBBmhlaWdodAMCB2Fycl9sZW4DAwdvbGRfYXJyAwQJY29weUFycmF5AAILdXBkYXRlUnVsZXMAAwVydWxlcwMFCXJ1bGVzX2xlbgMGB2dldENlbGwABA1nZXROZWlnaGJvdXJzAAUQcnVuR2FtZUFsZ29yaXRobQAGB25ld19hcnIDBwxfX2Rzb19oYW5kbGUDCApfX2RhdGFfZW5kAwkNX19nbG9iYWxfYmFzZQMKC19faGVhcF9iYXNlAwsNX19tZW1vcnlfYmFzZQMMDF9fdGFibGVfYmFzZQMNCsYLBwIAC1EBAX8jgICAgABBEGsiAiAANgIMIAIgATYCCEEAIAIoAgw2AoCIgIAAQQAgAigCCDYChIiAgABBACACKAIMIAIoAghsNgKIiICAAEGQiICAAAtrAQF/I4CAgIAAQRBrIgMgADYCDCADIAE2AgggAyACNgIEIANBADYCAAJAA0AgAygCACADKAIESEEBcUUNASADKAIIIAMoAgBqIAMoAgwgAygCAGotAAA6AAAgAyADKAIAQQFqNgIADAALCwtwAQF/I4CAgIAAQRBrIgIgADYCDCACIAE2AgggAkEANgIEAkADQCACKAIEIAIoAghIQQFxRQ0BIAIoAgQgAigCDCACKAIEai0AADoAoNaAgAAgAiACKAIEQQFqNgIEDAALC0EAIAIoAgg2AqDegIAAC5wBAQF/I4CAgIAAQRBrIgIgADYCCCACIAE2AgQCQAJAAkAgAigCCEEASEEBcQ0AIAIoAgRBAEhBAXENACACKAIIQQAoAoCIgIAASkEBcQ0AIAIoAgRBACgChIiAgABKQQFxRQ0BCyACQQA6AA8MAQsgAiACKAIEQQAoAoCIgIAAbCACKAIIai0AkIiAgAA6AA8LIAItAA9BGHRBGHULqQIBB38jgICAgABBEGsiAiSAgICAACACIAA2AgwgAiABNgIIIAIoAgxBAWsgAigCCEEBaxCEgICAACEBIAIoAgxBAWsgAigCCBCEgICAACEAIAIoAgxBAWsgAigCCEEBahCEgICAACEDIAIoAgwgAigCCEEBaxCEgICAACEEIAIoAgwgAigCCEEBahCEgICAACEFIAIoAgxBAWogAigCCEEBaxCEgICAACEGIAIoAgxBAWogAigCCBCEgICAACEHIAIoAgxBAWogAigCCEEBahCEgICAACEIIAJBEGokgICAgAAgAUEYdEEYdSAAQRh0QRh1aiADQRh0QRh1aiAEQRh0QRh1aiAFQRh0QRh1aiAGQRh0QRh1aiAHQRh0QRh1aiAIQRh0QRh1agvIBQEBfyOAgICAAEEgayIAJICAgIAAQZCIgIAAQbDegIAAQQAoAoiIgIAAEIKAgIAAIABBADYCHAJAA0AgACgCHEEAKAKIiICAAEhBAXFFDQEgACAAKAIcQQAoAoCIgIAAbzYCGCAAIAAoAhxBACgCgIiAgABtNgIUIAAgACgCGCAAKAIUEIWAgIAANgIQIABBADYCDAJAA0AgACgCDEEAKAKg3oCAAExBAXFFDQECQAJAAkAgACgCDC0AoNaAgABBGHRBGHVB7ABGQQFxRQ0AIAAoAhAgACgCDEEBai0AoNaAgABBGHRBGHVBMGtIQQFxRQ0AIAAoAhwtAJCIgIAAQf8BcUEAQf8BcUdBf3NBf3NBAXEgACgCDEEDai0AoNaAgABBGHRBGHVBMGtBAEdBf3NBf3NBAXFHQQFxDQELAkAgACgCDC0AoNaAgABBGHRBGHVBPUZBAXFFDQAgACgCECAAKAIMQQFqLQCg1oCAAEEYdEEYdUEwa0ZBAXFFDQAgACgCHC0AkIiAgABB/wFxQQBB/wFxR0F/c0F/c0EBcSAAKAIMQQNqLQCg1oCAAEEYdEEYdUEwa0EAR0F/c0F/c0EBcUdBAXENAQsgACgCDC0AoNaAgABBGHRBGHVB7QBGQQFxRQ0BIAAoAhAgACgCDEEBai0AoNaAgABBGHRBGHVBMGtKQQFxRQ0BIAAoAhwtAJCIgIAAQf8BcUEAQf8BcUdBf3NBf3NBAXEgACgCDEEDai0AoNaAgABBGHRBGHVBMGtBAEdBf3NBf3NBAXFHQQFxRQ0BCyAAKAIcIAAoAhwtALDegIAAQf8BcUEAQf8BcUdBf3NBAXE6ALDegIAACyAAIAAoAgxBBWo2AgwMAAsLIAAgACgCHEEBajYCHAwACwtBsN6AgABBkIiAgABBACgCiIiAgAAQgoCAgAAgAEEgaiSAgICAAAsAfgRuYW1lAWMHABFfX3dhc21fY2FsbF9jdG9ycwELYWNjZXB0QXJyYXkCCWNvcHlBcnJheQMLdXBkYXRlUnVsZXMEB2dldENlbGwFDWdldE5laWdoYm91cnMGEHJ1bkdhbWVBbGdvcml0aG0HEgEAD19fc3RhY2tfcG9pbnRlcgA2CXByb2R1Y2VycwEMcHJvY2Vzc2VkLWJ5AQxVYnVudHUgY2xhbmcPMTQuMC4wLTF1YnVudHUx");let f=new Int8Array,w,F,c,Q,u,r=100,a=100,g,s,d,h,l,B={x:0,y:0,down:!1,delete:!1},C={now:0,last:0,tick:0},b="#8f00ff",D="#444444",y=!1,E,N=(n,A,e)=>{let o=n/g,t=A/g;f[~~t*r+~~o]=e},m=(n,A,e,o)=>{l.beginPath(),l.moveTo(n,A),l.lineTo(e,o),l.stroke()},x=()=>{C.now=new Date().getTime();let n=C.now-C.then;C.then=C.now,C.tick+=n,y?B.down&&N(B.x,B.y,!B.delete):C.tick>=600&&(F(),f=new Int8Array(c.buffer,u(r,a),r*a),C.tick=0),l.fillStyle=b,l.strokeStyle=D,l.clearRect(0,0,window.innerWidth,window.innerHeight);for(let A=0;A<r;A++)m(A*g,0,A*g,window.innerHeight);for(let A=0;A<a;A++)m(0,A*g,window.innerWidth,A*g);for(let A=0;A<f.length;A++){let e=f[A],o=A%r*g,t=~~(A/r)*g;e&&l.fillRect(o,t,g,g)}};R({env:{consoleLog:console.log}}).then(n=>{g=window.innerWidth>window.innerHeight?window.innerWidth/r:window.innerHeight/a,window.innerWidth<window.innerHeight?r=1+~~(window.innerWidth/g):a=1+~~(window.innerHeight/g),u=n.exports.acceptArray,Q=n.exports.updateRules,c=n.exports.memory,F=n.exports.runGameAlgorithm,f=new Int8Array(c.buffer,u(r,a),r*a),E+=r*a*Int8Array.BYTES_PER_ELEMENT,E+=4*Int32Array.BYTES_PER_ELEMENT,w="l2=0 m3=0 =3=1";let A=new Int8Array(c.buffer,E,w.length);A.set(new TextEncoder().encode(w)),Q(E,A.length),s=document.querySelector("#rules"),h=document.querySelector("#paused"),d=document.querySelector("input"),l=document.querySelector("#canvas").getContext("2d"),l.canvas.width=window.innerWidth,l.canvas.height=window.innerHeight,window.onscroll=e=>{},window.onkeydown=e=>{document.querySelector("#notes").classList.add("hidden"),e.key=="Shift"&&s.classList.toggle("hidden"),s.classList.contains("hidden")||d.focus(),e.key==" "&&(y=!0,h.classList.remove("hidden")),e.key=="x"&&(B.delete=!0)},window.onkeyup=e=>{e.key==" "&&(y=!1,h.classList.add("hidden")),e.key=="x"&&(B.delete=!1)},s.onkeydown=e=>{if(e.code!="Enter"&&e.key!="Escape")return;s.classList.add("hidden");let o=new Int8Array(c.buffer,E,d.value.length?d.value.length:14);o.set(new TextEncoder().encode(d.value||"l2=0 m3=0 =3=1")),Q(o,o.length)},window.onmousedown=window.onmouseup=e=>{B.down=e.type=="mousedown"},window.onmousemove=e=>{B.x=e.clientX,B.y=e.clientY},C.now=new Date().getTime(),C.then=C.now-1/60,setInterval(x,60)});
