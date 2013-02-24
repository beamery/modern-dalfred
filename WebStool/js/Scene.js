/*global APP:true, THREE:true, gl:true */

var APP = APP || {};

APP.FEET_PER_WORLD_UNIT = 0.4;

APP.Scene = APP.Klass(null, {

    _init: function() {
        'use strict';
        this.terrain = new APP.Terrain(32);
    },

    draw: function() {
        'use strict';
        //mv.push();

        this.terrain.draw();

        //mv.pop();
    }
});
