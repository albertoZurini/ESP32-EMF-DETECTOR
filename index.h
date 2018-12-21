const char MAIN_page[] PROGMEM = R"=====(
  <html>
  <head>
      <title>Realtime Analytics</title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
  </head>
  <body>
    <h1>Reading: <span id="output"></span></h1>
    <div id="chartContainer" style="height: 50vh; width:100%;"></div>

    
  </body>
  <script src="https://canvasjs.com/assets/script/canvasjs.min.js"></script>
  <script>
  var wsUri = "ws://192.168.4.1:81/";
  var output, dps = [], chart;
  var xVal = 0, dataLength = 20;

  function init()
  {
    output = document.getElementById("output");
    testWebSocket();

    chart = new CanvasJS.Chart("chartContainer", {
      title :{
        text: "Dynamic Data"
      },
      axisY: {
        minimum: 0,
        maximum: 4096
      },      
      data: [{
        type: "line",
        dataPoints: dps
      }]
    });
  }

  function updateChart(yVal){
    console.log(yVal, typeof yVal);
    yVal = parseInt(yVal);
    dps.push({
      x: xVal,
      y: yVal
    });
    xVal++;
    console.log(dps[0]);

    if (dps.length > dataLength) {
      dps.shift();
    }

    chart.render();
  }

  function testWebSocket()
  {
    websocket = new WebSocket(wsUri);
    websocket.onopen = (evt) =>{
      console.log('Socket open');
    };
    websocket.onclose = (evt) => {
      console.log('Close');
    };
    websocket.onmessage = (evt) => {
      let val = JSON.parse(evt.data).adc;
      console.log('Message ', evt.data);
      document.getElementById('output').innerText = val;
      updateChart(val);
    };
    websocket.onerror = (evt) => {
      console.error(evt.data);
    };
  }

  window.addEventListener("load", init, false);
  </script>
</html>
)=====";