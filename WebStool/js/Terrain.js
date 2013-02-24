/*global APP:true, THREE:true, gl:true */

var APP = APP || {};

/**
 * A class to handle the terrain of our scene. Terrain is an xz-plane,
 * possibly augmented in the future by a height mapping.
 *
 * Note: Measurements for the terrain are in FEET.
 */
APP.Terrain = APP.Klass(null, {

    _init: function(size) {
        'use strict';
        var vxs = [];
        for (var i = 0; i < size; i++) {
            var tmp = [];
            for (var j = 0; j < size; j++) {
                tmp.push(new THREE.Vector3(j, 0, i));
            }
            vxs.push(tmp);
        }
        this.mesh = new APP.Mesh(vxs);
    },

    draw: function() {
        'use strict';
        this.mesh.draw();
    }
});