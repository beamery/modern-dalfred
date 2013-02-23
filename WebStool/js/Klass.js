/*global APP:true */

var APP = APP || {};

/**
 * Klasses provide for easy object creation and inheritance patterns. They 
 * allow for an interface more similar to classical object-oriented creation
 * patterns. Private members should be named with leading underscores.
 *
 * Example Klass:
 *
 *  var Cat = Klass(Animal, {
 *
 *    _init: function() {
 *      // initialize Cat
 *    },
 *
 *     talk: function() {
 *       console.log(says);
 *     },
 *
 *     says: "meow"
 *  })
 *
 */
APP.Klass = function(Parent, props) {
  'use strict';

  var Child, F, i;

  // new constructor
  Child = function () {
    if (Child._super && Child._super.hasOwnProperty("_init")) {
        Child._super._init.apply(this, arguments);
    }
    if (Child.prototype.hasOwnProperty("_init")) {
        Child.prototype._init.apply(this, arguments);
    }
  };

  // inherit from Parent if one exists. Otherwise, enherit from Object
  Parent = Parent || Object;
  F = function () {};
  F.prototype = Parent.prototype;
  Child.prototype = new F();
  Child._super = Parent.prototype;
  Child.prototype.constructor = Child;

  // add implementation methods
  for (i in props) {
    if (props.hasOwnProperty(i)) {
        Child.prototype[i] = props[i];
    }
  }

  // return the Klass
  return Child;
};