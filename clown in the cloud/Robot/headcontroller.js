module.exports = function() {
    
    var servoModule = require('jsupm_servo');

    var xServo = new servoModule.Servo(10);
    var yServo = new servoModule.Servo(10);
    
    
    
    function lookUp() {
        console.log("Head: up");
        yServo.setAngle(120);
    }
    
    function lookMiddle() {
        console.log("Head: middle");
        yServo.setAngle(90);
        xServo.setAngle(90);
    }
    
    function lookLeft() {
        console.log("Head: Left");
        xServo.setAngle(60);
    }
    
    function lookRight() {
        console.log("Head: Right");
        xServo.setAngle(120);
    }
    
    lookMiddle();
    
  return {
      lookUp: lookUp,
      lookMiddle: lookMiddle,
      lookLeft: lookLeft,
      lookRight: lookRight
  };
}();