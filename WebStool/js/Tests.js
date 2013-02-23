/*global yepnope:true, APP:true, THREE:true */

var APP = APP || {};

APP.runTests = function() {
    APP._testMatStack();
};

APP._testMatStack = function() {
    var matStack = new APP.MatStack();

    try {
        matStack.pop();
        console.log('Pop should have caused an exception to be thrown');
    } catch(e) {}

    matStack.push();

    matStack.print();
    console.log('-');

    matStack.active.translate(new THREE.Vector3(3, 2, 5));


    matStack.print();
    console.log('-');

    matStack.push();

    matStack.active.rotateByAxis(new THREE.Vector3(1, 0, 0), 90);

    matStack.print();
    console.log('-');

    matStack.pop();

    matStack.print();
    console.log('-');

    matStack.active.translate(new THREE.Vector3(4, 1, 2));
    matStack.print();
    console.log('-');

    matStack.push();

    matStack.active.translate(new THREE.Vector3(4, 1, 2));
    matStack.push();

    matStack.active.translate(new THREE.Vector3(4, 1, 2));
    matStack.push();

    matStack.pop();
    matStack.pop();
    matStack.pop();

    matStack.print();
    console.log('-');

    matStack.pop();
    
    matStack.print();
    console.log('-');
};