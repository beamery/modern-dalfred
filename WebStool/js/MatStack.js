/*global APP:true, THREE:true */

var APP = APP || {};

/**
 * Extend three.js Matrix4 to have a print function which
 * prints out the matrix in a human-readable format
 */
THREE.Matrix4.prototype.print = function() {
    'use strict';
    var str;
    for (var i = 0; i < 4; i++) {
        str = '[';
        for (var j = 0; j < 4; j++) {
            str += '\t' + this.elements[4*j + i]; //.toFixed(2);
        }
        str += '\t]';
        console.log(str);
    }
};

APP.MatStack = APP.Klass(null, {

    /**
     * Initialize the stack to be empty, and the active matrix
     * to be the identity matrix
     */
    _init: function() {
        'use strict';
        this.stack = [];
        this.active = new THREE.Matrix4();
    },

    /**
     * Push the active matrix onto the top of the stack. Active matrix
     * remains active.
     */
    push: function() {
        'use strict';
        // first make a copy, then push. Don't want to just push the reference
        var m = new THREE.Matrix4();
        m.copy(this.active);
        this.stack.push(m);
    },

    /**
     * Pop the matrix off the top of the stack and set it to the new active
     * matrix.
     */
    pop: function() {
        'use strict';
        if (this.stack.length === 0) {
            throw {
                name: "MatStack Error",
                message: "Tried to pop off an empty stack"
            };
        }
        this.active = this.stack.pop();
    },

    /**
     * Print the matrix stack's active matrix.
     */
    print: function() {
        'use strict';
        /*
        var str;
        for (var i = 0; i < 4; i++) {
            str = '[';
            for (var j = 0; j < 4; j++) {
                str += '\t' + this.active.elements[4*j + i]; //.toFixed(2);
            }
            str += '\t]';
            console.log(str);
        }
        */
        this.active.print();
    }
});

