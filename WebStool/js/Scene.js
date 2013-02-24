/*global APP:true, THREE:true, gl:true */

var APP = APP || {};

APP.FEET_PER_WORLD_UNIT = 0.4;
APP.SCENE_SIZE = 6;

APP.Scene = APP.Klass(null, {

    _init: function() {
        'use strict';
        this.terrain = new APP.Terrain(APP.SCENE_SIZE);
        this.disk = new APP.Disk(2.0, 5.0, 11);
    },

    draw: function(mvs) {
        'use strict';
        mvs.push();

        // set scale down to feet
        mvs.active.scale(new THREE.Vector3(
            APP.FEET_PER_WORLD_UNIT,
            APP.FEET_PER_WORLD_UNIT,
            APP.FEET_PER_WORLD_UNIT));


        // center the grid on the screen
        //mvs.active.translate(
            //new THREE.Vector3(-APP.SCENE_SIZE / 2, 0.0, -APP.SCENE_SIZE / 2));

        this.terrain.draw();

        mvs.active.translate(new THREE.Vector3(0.0, 2.0, 0.0));
        this.disk.draw();


        mvs.pop();
    }
});
