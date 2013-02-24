/*global APP:true, THREE:true, gl:true */

var APP = APP || {};

/**
 * A mesh is a way to store vertices in a continuous ordering.
 * Initially passed in as a grid stored in a 2D array, the vertices are shuffled
 * around a bit and stored as an array of floats, in order to make them quicker
 * to draw.
 */
APP.Mesh = APP.Klass(null, {

    /**
     * Convert the grid into something useful to GL. This handles most of the
     * heavy lifting for the Mesh class. Based on the grid, creates an array
     * which can be drawn as a bunch of triangles.
     *
     * The grid must go from left to right, bottom to top, according the the
     * outside of the mesh.
     *
     *  a    b    c
     *  *----*----*
     *  |\   |\   |
     *  | \  | \  |
     *  |  \ |  \ |
     *  |   \|   \|
     *  *----*----*
     *  d    e    f
     *
     *  when at vertex 'e', you would draw 'eab' and then 'ebf'
     *
     */
     _init: function(grid) {
        'use strict';
        this.vxs = [];

        // number of rows - 1 so that we don't run out of bounds
        for (var i = 0; i < grid.length - 1; i++) {
            for (var j = 0; j < grid[0].length; j++) {

                // If we are at any row but the first, construct the
                // previous triangle
                if (j !== 0) {
                    // current (row, col)
                    this.vxs.push(grid[i][j].x);
                    this.vxs.push(grid[i][j].y);
                    this.vxs.push(grid[i][j].z);

                    // up and left (row+1, col-1)
                    this.vxs.push(grid[i+1][j-1].x);
                    this.vxs.push(grid[i+1][j-1].y);
                    this.vxs.push(grid[i+1][j-1].z);

                    // up (row+1, col)
                    this.vxs.push(grid[i+1][j].x);
                    this.vxs.push(grid[i+1][j].y);
                    this.vxs.push(grid[i+1][j].z);
                }

                // If we are at any row but the last, construct the
                // following triangle
                if (j !== grid[0].length - 1) {
                    // current (row, col)
                    this.vxs.push(grid[i][j].x);
                    this.vxs.push(grid[i][j].y);
                    this.vxs.push(grid[i][j].z);

                    // up (row+1, col)
                    this.vxs.push(grid[i+1][j].x);
                    this.vxs.push(grid[i+1][j].y);
                    this.vxs.push(grid[i+1][j].z);

                    // right (row, col+1)
                    this.vxs.push(grid[i][j+1].x);
                    this.vxs.push(grid[i][j+1].y);
                    this.vxs.push(grid[i][j+1].z);
                }
            }
        }
        this._initBuffer();
        this._initWireframe(grid);

    },

    /**
     * create a GL vertex buffer for this mesh
     */
    _initBuffer: function() {
        'use strict';
        this.vxPosBuf = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, this.vxPosBuf);
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(this.vxs), gl.STATIC_DRAW);
        this.itemSize = 3;
        this.numItems = this.vxs.length / 3;
    },

    /**
     * Make a wireframe version of this mesh. This builds two sets of lines,
     * which zig-zag back and forth and result in a wireframe-like shape.
     *
     * This allows us to make just one draw call for the mesh rather than
     * making one draw call for each triangle within the mesh.
     */
    _initWireframe: function(grid) {
        'use strict';
        var i, j;
        this.wireframeVxs = [];

        // store the first zig-zag pattern
        for (i = 0; i < grid.length; i++) {
            for (j = 0; j < grid[0].length; j++) {
                if (i % 2 === 0) {
                    this.wireframeVxs.push(grid[i][j].x);
                    this.wireframeVxs.push(grid[i][j].y);
                    this.wireframeVxs.push(grid[i][j].z);
                }
                else {
                    this.wireframeVxs.push(grid[i][grid[0].length - 1 - j].x);
                    this.wireframeVxs.push(grid[i][grid[0].length - 1 - j].y);
                    this.wireframeVxs.push(grid[i][grid[0].length - 1 - j].z);
                }
            }
        }

        // Retrace back to the first vertex, avoiding the case in which the
        // second zig-zag causes a diagonal line across the mesh
        /*
        if (grid.length % 2 === 0) {
            for (i = grid.length - 1; i >= 0; i--) {
                this.wireframeVxs.push(grid[i][grid.length - 1].x);
                this.wireframeVxs.push(grid[i][grid.length - 1].y);
                this.wireframeVxs.push(grid[i][grid.length - 1].z);
            }
        }*/

        // store the second zig-zag
        for (i = grid[0].length - 1; i >= 0; i--) {
            for (j = grid.length - 1; j >= 0; j--) {
                if (i % 2 === 1) {
                    this.wireframeVxs.push(grid[j][i].x);
                    this.wireframeVxs.push(grid[j][i].y);
                    this.wireframeVxs.push(grid[j][i].z);
                }
                else {
                    this.wireframeVxs.push(grid[grid.length - 1 - j][i].x);
                    this.wireframeVxs.push(grid[grid.length - 1 - j][i].y);
                    this.wireframeVxs.push(grid[grid.length - 1 - j][i].z);
                }
            }
        }
        this._initWireframeBuffer();
    },

    /**
     * Initialize GL buffer for the wireframe mesh
     */
    _initWireframeBuffer: function() {
        'use strict';
        this.wireframeVxBuf = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, this.wireframeVxBuf);
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(this.wireframeVxs), gl.STATIC_DRAW);
        this.wfItemSize = 3;
        this.wfNumItems = this.wireframeVxs.length / 3;
        
    },

    draw: function(wireframe) {
        'use strict';
        wireframe = wireframe || APP.wireframe;
        if (!wireframe) {
            gl.bindBuffer(gl.ARRAY_BUFFER, this.vxPosBuf);
            gl.vertexAttribPointer(APP.shaderProgram.vertexPosAttrib, this.itemSize, gl.FLOAT, false, 0, 0);
            APP.setMatrixUniforms();
            gl.drawArrays(gl.TRIANGLES, 0, this.numItems);
        }
        else {
            gl.bindBuffer(gl.ARRAY_BUFFER, this.wireframeVxBuf);
            gl.vertexAttribPointer(APP.shaderProgram.vertexPosAttrib, this.wfItemSize, gl.FLOAT, false, 0, 0);

            // if we're drawing a wireframe, we should be able to see through it
            gl.disable(gl.DEPTH_TEST);
            APP.setMatrixUniforms();
            gl.drawArrays(gl.LINE_STRIP, 0, this.wfNumItems);
            gl.enable(gl.DEPTH_TEST);
        }
    }
});

