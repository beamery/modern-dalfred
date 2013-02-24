/*global yepnope:true, APP:true, THREE:true */
/*jshint bitwise: false */

// initialize global variables
var APP = APP || {};
var included = [
    'js/Klass.js',
    'js/Tests.js',
    'js/MatStack.js',
    'js/Mesh.js',
    'js/Terrain.js',
    'js/Scene.js'
];

var gl,
    canvas,
    mvs,
    proj,
    triVertPosBuf,
    scene;

APP.shaderProgram = null;
APP.wireframe = true;

function initGL(canvas) {
    'use strict';
    // initialize context if we can
    try {
        gl = canvas.getContext('webgl') || canvas.getContext('experimental-webgl');
    } catch (e) {}

    // If we don't have a GL context, give up.
    if (!gl) {
        alert('Unable to initialize WebGL. Your browser may not support it.');
    }
}

function createShader(type, id) {
    'use strict';
    // get the HTML element containing the shader
    var src = document.getElementById(id);
    if (!src) {
        throw {
            name: 'Shader initialization error',
            message: 'Failed to get shader from HTML doc'
        };
    }

    // dump the shader text into a string
    var str = '';
    var text = src.firstChild;
    while (text) {
        if (text.nodeType === 3) {
            str += text.textContent;
        }
        text = text.nextSibling;
    }

    // create the shader, attach it to the text, and then compile it
    var shader = gl.createShader(type);
    gl.shaderSource(shader, str);
    gl.compileShader(shader);

    // if there was a problem creating the shader, alert the user
    if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
        console.log(str);
        console.log(gl.getShaderInfoLog(shader));
        alert(id + ' failed to compile');
        return null;
    }
    else {
        console.log(id + ' compiled successfully');
    }

    return shader;
}

function initShaders() {
    'use strict';
    var frag = createShader(gl.FRAGMENT_SHADER, "frag-shader");
    var vert = createShader(gl.VERTEX_SHADER, "vert-shader");

    // create the program, attach the shaders, and then link the program
    APP.shaderProgram = gl.createProgram();
    gl.attachShader(APP.shaderProgram, vert);
    gl.attachShader(APP.shaderProgram, frag);
    gl.linkProgram(APP.shaderProgram);

    // check whether or not shaders linked correctly
    if (!gl.getProgramParameter(APP.shaderProgram, gl.LINK_STATUS)) {
        alert('Could not initialize shaders');
    }

    gl.useProgram(APP.shaderProgram);

    // get a handle for the vertexPos shader attribute
    APP.shaderProgram.vertexPosAttrib = gl.getAttribLocation(APP.shaderProgram, 'vertexPos');
    gl.enableVertexAttribArray(APP.shaderProgram.vertexPosAttrib);

    // get a handle for the mView and proj shader uniforms
    APP.shaderProgram.mView = gl.getUniformLocation(APP.shaderProgram, 'mView');
    APP.shaderProgram.proj = gl.getUniformLocation(APP.shaderProgram, 'proj');
}


APP.setMatrixUniforms = function() {
    'use strict';
    // flatten modelview and projection matrices for use in shaders
    var projFlat = [], mViewFlat = [];
    proj.flattenToArray(projFlat);
    mvs.active.flattenToArray(mViewFlat);

    // push the values of our modelview and projection matrices into their
    // shader locations
    gl.uniformMatrix4fv(APP.shaderProgram.proj, false, new Float32Array(projFlat));
    gl.uniformMatrix4fv(APP.shaderProgram.mView, false, new Float32Array(mViewFlat));
};


// test function, not to be used in production
function initBuffers() {
    'use strict';
    triVertPosBuf = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, triVertPosBuf);
    var vertices = [
         0.0,  1.0,  0.0,
        -1.0, -1.0,  0.0,
         1.0, -1.0,  0.0
    ];
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
    triVertPosBuf.itemSize = 3;
    triVertPosBuf.numItems = 3;
}

function drawScene() {
    'use strict';

    // reset the modelview and projection matrices
    proj.makePerspective(50, gl.viewportWidth / gl.viewportHeight, 0.1, 50.0);
    mvs.active.identity();

    // update the viewport and clear the screen
    gl.viewport(0, 0, canvas.width, canvas.height);
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

    // move whole scene so that we can see it
    mvs.active.translate(new THREE.Vector3(0.0, -2.0, -7.0));

    // draw the scene
    mvs.push();

    mvs.active.rotateY(3 * Math.PI / 4);
    //mvs.active.rotateY( 0.005 * (new Date().getTime()));
    gl.bindBuffer(gl.ARRAY_BUFFER, triVertPosBuf);
    gl.vertexAttribPointer(APP.shaderProgram.vertexPosAttrib, triVertPosBuf.itemSize, gl.FLOAT, false, 0, 0);
    APP.setMatrixUniforms();
    //gl.drawArrays(gl.TRIANGLES, 0, triVertPosBuf.numItems);
    scene.draw();

    mvs.pop();

}

/**
 * This is the main program loop.
 */
function tick() {
    'use strict';
    drawScene();
    window.requestAnimationFrame(tick);
}

function init() {
    'use strict';

    // before doing anything, run tests (stored in Tests.js)
    //APP.runTests();

    canvas = document.getElementById('myCanvas');
    mvs = new APP.MatStack();
    proj = new THREE.Matrix4();

    initGL(canvas); // init GL context
    initShaders();
    initBuffers();

    // only if WebGL is available
    if (gl) {
        gl.viewportWidth = canvas.width;
        gl.viewportHeight = canvas.height;
        gl.clearColor(0.2, 0.2, 0.2, 1.0);
        gl.enable(gl.DEPTH_TEST);
        gl.depthFunc(gl.LEQUAL);


        scene = new APP.Scene();
        tick();
    }
}

yepnope({
    load: included,
    complete: function () {
        'use strict';
        init();
    }
    });
