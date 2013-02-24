/*global yepnope:true, APP:true, THREE:true */

var APP = APP || {};

APP.runTests = function() {
    'use strict';
    console.log('running tests...');
    APP._testMatStack();
    //APP._testMesh();
};

APP._testMatStack = function() {
    'use strict';
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

APP._testMesh = function() {
    'use strict';
    var vxs = [];
    for (var i = 0; i < 5; i++) {
        var tmp = [];
        for (var j = 0; j < 5; j++) {
            tmp.push(new THREE.Vector3(j, 0, i));
        }
        vxs.push(tmp);
    }
    var mesh = new APP.Mesh(vxs);
    mesh.draw(true);
};