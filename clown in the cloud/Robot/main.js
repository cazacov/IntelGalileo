/*jslint node:true, vars:true, bitwise:true, unparam:true */
/*jshint unused:true */
/*global */

var ledController = require("./ledController.js");
ledController.clear();
ledController.smile();


var motorController = require("./motorController.js")
motorController.go();
motorController.stop();
//motorController.demo();

var headControler = require("./headcontroller.js");
headControler.lookMiddle();

var theThingsAPI = require('thethingsio-api');
var motionKEY = 'motion';

//create Client
var client = theThingsAPI.createClient();
var lastAction = "@@@";

function readMotions()
{
    //read latest write
    var req1 = client.thingReadLatest(motionKEY);

    //event fired when the response arrives
    req1.on('response',function(res){
        if (res.statusCode == 200 && res.payload !== undefined)
        {
            var payload = JSON.parse(res.payload);
            var newAction = payload.data[0].value;
            if (newAction !== lastAction)
            {
                lastAction = newAction;
                motorController.doAction(newAction);
            }
        }
    });
    req1.end();
}

readMotions();
motorController.stop();

var loopCounter = 0;
setInterval(function() {
    readMotions();
}, 200);
