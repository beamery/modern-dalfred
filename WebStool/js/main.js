/*global yepnope:true, APP:true, THREE:true */

// initialize global variables
var gl;
var APP = APP || {};


var included = [
    'js/Klass.js',
    'js/Tests.js',
    'js/MatStack.js'
];


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
    // get the HTML element containing the shader
    var src = document.getElementById(id);
    if (!src) {
        throw {
            name: 'Shader initialization error',
            message: 'Failed to get shader from HTML doc'
        };
    }

    // dump the shader text into a string
    str = '';
    var text = src.firstChild;
    while (text) {
        if (text.nodeType == 3) {
            str += text.textContent;
        }
        text = text.nextSibling;
    }

    // create the shader, attach it to the text, and then compile it
    var shader = gl.createShader(type);
    gl.shaderSource(shader, str);
    gl.compileShader(shader);

    // if there was a problem creating the shader, alert the user
    if (gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
        alert(gl.getShaderInfoLog(shader));
        return null;
    }

    return shader;
}

var shaderProgram;

function initShaders() {
    var frag = createShader(gl.FRAGMENT_SHADER, "frag-shader");
    var vert = createShader(gl.VERTEX_SHADER, "vert-shader");

    // create the program, attach the shaders, and then link the program
    shaderProgram = gl.createProgram();
    gl.attachShader(shaderProgram, vert);
    gl.attachShader(shaderProgram, frag);
    gl.linkProgram(shaderProgram);

    if (!gl.getProgramParameter(shaderProgram, gl.LINK_STATUS)) {
        alert('Could not initialize shaders');
    }

    gl.useProgram(shaderProgram);

    shaderProgram.vertexPosAttrib = gl.getAttribLocation(shaderProgram, 'vertextPos');
    gl.enableVertexAttribArray(shaderProgram.vertexPosAttrib);

    shaderProgram.mView = gl.getUniformLocation(shaderProgram, 'mView');
    shaderProgram.proj = gl.getUniformLocation(shaderProgram, 'proj');
}

var mView;
var proj;

function setMatrixUniforms() {
    gl.uniformMatrix4fv(shaderProgram.proj, false, proj);
    gl.uniformMatrix4fv(shaderProgram.mView, false, mView);
}


var triVertPosBuf;
var squVertPosBuf;

function initBuffers() {
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

    squVertPosBuf = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, squVertPosBuf);
    vertices = [
         1.0,  1.0,  0.0,
        -1.0,  1.0,  0.0,
         1.0, -1.0,  0.0,
        -1.0, -1.0,  0.0
    ];
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
    squVertPosBuf.itemSize = 3;
    squVertPosBuf.numItems = 3;
}

function drawScene() {
    proj = (new THREE.Matrix4()).makePerspective(50, gl.viewportWidth / gl.viewportHeight, 0.0, 10.0);
    mView = new THREE.Matrix4();

    gl.viewport(0.0, gl.viewportWidth, gl.viewportHeight);
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

    mView.translate(new THREE.Vector3(-1.5, 0.0, -7.0));
    gl.bindBuffer(gl.ARRAY_BUFFER, triVertPosBuf);
    gl.vertexAttribPointer(shaderProgram.vertexAttribPointer, triVertPosBuf.itemSize, gl.FLOAT, false, 0, 0);
    setMatrixUniforms();
    gl.drawArrays(gl.TRIANGLES, 0, triVertPosBuf.numItems);

    mView.translate(new THREE.Vector3(3.0, 0.0, 0.0));
    gl.bindBuffer(gl.ARRAY_BUFFER, squVertPosBuf);
    gl.vertexAttribPointer(shaderProgram.vertexAttribPointer, squVertPosBuf.itemSize, gl.FLOAT, false, 0, 0);
    setMatrixUniforms();
    gl.drawArrays(gl.TRIANGLE_STRIP, 0, 0, squVertPosBuf.numItems);


}

function init() {
    'use strict';

    // before doing anything, run tests (stored in Tests.js)
    console.log('running tests...');
    APP.runTests();

    var canvas = document.getElementById('myCanvas');

    initGL(canvas); // init GL context
    initShaders();
    initBuffers();

    // only if WebGL is available
    if (gl) {
        gl.viewportWidth = canvas.width;
        gl.viewportHeight = canvas.height;
        gl.clearColor(0.2, 0.3, 0.2, 1.0);
        gl.enable(gl.DEPTH_TEST);
        gl.depthFunc(gl.LEQUAL);
        gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
    }
    drawScene();
}

yepnope({
    load: included,
    complete: function () {
        'use strict';
        init();
    }
    });
