#pragma once
const char WEB_UI_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html><html lang="en"><head><meta charset="UTF-8">
<meta name="viewport" content="width=device-width,initial-scale=1,maximum-scale=1,user-scalable=no">
<title>RadioMicroscope</title><style>
*{margin:0;padding:0;box-sizing:border-box}
body{background:#0a0a0f;color:#e0e0e0;font-family:system-ui,-apple-system,sans-serif;max-width:480px;margin:0 auto;padding:8px}
header{display:flex;justify-content:space-between;align-items:center;padding:10px 12px;background:#141420;border:1px solid #1a1a2e;border-radius:8px;margin-bottom:8px}
header h1{font-size:15px;letter-spacing:2px;color:#00d4aa}
.status{font-size:12px;color:#888}
.status::before{content:'';display:inline-block;width:8px;height:8px;border-radius:50%;margin-right:5px;background:#ff4444;vertical-align:middle}
.status.on::before{background:#00d4aa}
.panel{background:#141420;border:1px solid #1a1a2e;border-radius:8px;padding:12px;margin-bottom:8px}
.panel h2{font-size:11px;letter-spacing:1.5px;color:#888;margin-bottom:8px}
#rssi-list{list-style:none}
#rssi-list li{display:flex;align-items:center;gap:6px;padding:4px 0;font-size:13px}
.net-name{flex:1;min-width:0;overflow:hidden;text-overflow:ellipsis;white-space:nowrap}
.net-rssi{font-family:'Courier New',monospace;font-size:12px;color:#888;width:70px;text-align:right;flex-shrink:0}
.rssi-bar{flex:0 0 80px;height:8px;background:#1a1a2e;border-radius:4px;overflow:hidden}
.rssi-fill{height:100%;background:#00d4aa;border-radius:4px;transition:width .3s}
.imu-row{display:flex;gap:16px;font-size:14px}
.imu-row label{color:#888;font-size:11px;letter-spacing:1px}
.imu-row span{font-family:'Courier New',monospace;font-size:18px;color:#00d4aa}
.ctrl{margin-top:6px}
.ctrl-header{display:flex;justify-content:space-between;align-items:baseline}
.ctrl-val{font-family:'Courier New',monospace;font-size:16px;color:#00d4aa}
input[type=range]{-webkit-appearance:none;appearance:none;width:100%;height:6px;background:#1a1a2e;border-radius:3px;outline:none;margin:10px 0}
input[type=range]::-webkit-slider-thumb{-webkit-appearance:none;width:44px;height:44px;border-radius:50%;background:#00d4aa;cursor:pointer;border:none}
input[type=range]::-moz-range-thumb{width:44px;height:44px;border-radius:50%;background:#00d4aa;cursor:pointer;border:none}
.range-labels{display:flex;justify-content:space-between;font-size:11px;color:#888;margin-top:-4px}
.trim-row{display:flex;align-items:center;gap:6px;margin-top:8px;font-size:12px;color:#888}
.trim-row input{width:70px;background:#0a0a0f;border:1px solid #1a1a2e;color:#e0e0e0;border-radius:4px;padding:4px 6px;font-family:'Courier New',monospace;font-size:13px;text-align:center}
</style></head><body>
<header><h1>RADIOMICROSCOPE</h1><span class="status" id="conn">Disconnected</span></header>
<section class="panel"><h2>RSSI MONITOR</h2><ul id="rssi-list"><li style="color:#888">Waiting for data&hellip;</li></ul></section>
<section class="panel"><h2>ORIENTATION</h2><div class="imu-row"><div><label>PITCH</label><br><span id="pitch">--</span></div><div><label>ROLL</label><br><span id="roll">--</span></div></div></section>
<section class="panel"><h2>AZIMUTH (SPEED)</h2><div class="ctrl"><div class="ctrl-header"><span class="range-labels">&#9664; CCW</span><span class="ctrl-val" id="az-val">0%</span><span class="range-labels">CW &#9654;</span></div><input type="range" min="-100" max="100" value="0" id="az"><div class="trim-row">Trim: <input type="number" min="-50" max="50" value="0" id="trim"> &micro;s</div></div></section>
<section class="panel"><h2>ELEVATION (ANGLE)</h2><div class="ctrl"><div class="ctrl-header"><span></span><span class="ctrl-val" id="el-val">90&deg;</span></div><input type="range" min="0" max="180" value="90" id="el"><div class="range-labels"><span>0&deg;</span><span>180&deg;</span></div></div></section>
<script>
var ws,az=document.getElementById('az'),el=document.getElementById('el'),trim=document.getElementById('trim'),conn=document.getElementById('conn');
trim.value=localStorage.getItem('azTrim')||0;
function connect(){
ws=new WebSocket('ws://'+location.host+'/ws');
ws.onopen=function(){conn.textContent='Connected';conn.className='status on'};
ws.onclose=function(){conn.textContent='Disconnected';conn.className='status';setTimeout(connect,3000)};
ws.onmessage=function(e){var d=JSON.parse(e.data);if(d.type==='sensors'){updateIMU(d.pitch,d.roll);updateRSSI(d.networks)}};
}
var sendTimer=null;
function sendControl(){
if(sendTimer)return;
sendTimer=setTimeout(function(){sendTimer=null;
if(ws&&ws.readyState===1)ws.send(JSON.stringify({type:'control',azimuth:parseInt(az.value),elevation:parseInt(el.value),trim:parseInt(trim.value)}))},50);
}
function updateRSSI(networks){
var list=document.getElementById('rssi-list');list.innerHTML='';
networks.forEach(function(n){var pct=Math.max(0,Math.min(100,(n.rssi+90)*100/60));
var li=document.createElement('li');
li.innerHTML='<span class="net-name">'+(n.ssid||'(hidden)')+'</span><span class="net-rssi">'+n.rssi+' dBm</span><div class="rssi-bar"><div class="rssi-fill" style="width:'+pct+'%"></div></div>';
list.appendChild(li)});
}
function updateIMU(p,r){document.getElementById('pitch').textContent=p.toFixed(1)+'\u00B0';document.getElementById('roll').textContent=r.toFixed(1)+'\u00B0'}
az.oninput=function(){document.getElementById('az-val').textContent=az.value+'%';sendControl()};
az.onmouseup=az.ontouchend=function(){az.value=0;document.getElementById('az-val').textContent='0%';sendControl()};
el.oninput=function(){document.getElementById('el-val').textContent=el.value+'\u00B0';sendControl()};
trim.onchange=function(){localStorage.setItem('azTrim',trim.value);sendControl()};
connect();
</script></body></html>
)rawliteral";
