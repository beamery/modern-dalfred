/*global APP:true, THREE:true, gl:true */

var APP = APP || {};

/**
 * A disk shape, possibly with a hole in the middle. The disk may have
 * a height. Make sure that inner radius is smaller than outer radius. If it
 * is not, lighting may be broken.
 *
 * Note: By default, outer radius is always on the bottom
 *
 * TODO: Make sure that this class doesn't break when lighting is applied
 */
APP.SkewedDisk = APP.Klass(null, {

    _init: function(innerRad, outerRad, slices, height) {
        'use strict';
        height = height || 0;
        var theta;

        var vxs = [];

        // construct lower(outer) circle
        vxs.push([]);
        for (theta = 0; theta <= 2 * Math.PI; theta += 2 * Math.PI / slices) {
            vxs[0].push(new THREE.Vector3(
                Math.cos(theta) * outerRad, 0.0, Math.sin(theta) * outerRad));
        }
        // one more vertex for continuity
        vxs[0].push(new THREE.Vector3(
            Math.cos(0) * outerRad, 0.0, Math.sin(0) * outerRad));

        // construct upper(inner) circle
        vxs.push([]);
        for (theta = 0; theta <= 2 * Math.PI; theta += 2 * Math.PI / slices) {
            vxs[1].push(new THREE.Vector3(
                Math.cos(theta) * innerRad, height, Math.sin(theta) * innerRad));
        }
        vxs[1].push(new THREE.Vector3(Math.cos(0) * innerRad, height, Math.sin(0) * innerRad));

        this.mesh = new APP.Mesh(vxs);
    },

    draw: function() {
        'use strict';
        this.mesh.draw();
    }

});


/**
 * A simple wrapper around the SkewedDisk class, initialized with height 0.
 */
APP.Disk = APP.Klass(APP.SkewedDisk, {

    _init: function(innerRad, outerRad, slices) {
        'use strict';
        // simply calls the _init method of the parent class (SkewedDisk),
        // but with a height of 0 (done implicitly).
        //APP.Disk._super._init.apply(this, arguments);
    },

    draw: function() {
        'use strict';
        this.mesh.draw();
    }
});