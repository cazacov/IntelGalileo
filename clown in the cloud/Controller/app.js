var keypress = require('keypress');
var robotController = require("./robotcontroller.js")

// make `process.stdin` begin emitting "keypress" events
keypress(process.stdin);

// listen for the "keypress" event
process.stdin.on('keypress', function (ch, key) {

  if (key && key.ctrl && key.name == 'c') {
    process.stdin.pause();
  }
  else
  {
    console.log(key.name);
    robotController.processKey(key.name);
  }

});

process.stdin.setRawMode(true);
process.stdin.resume();

robotController.sendAction("stop");

