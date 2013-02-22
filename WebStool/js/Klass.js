/*global APP:true */

APP.Klass = function(Parent, props) {
  'use strict';

  var Child, F, i;

  // new constructor
  Child = function () {
    if (Child.super && Child.super.hasOwnProperty("_init")) {
        Child.super._init.apply(this, arguments);
    }
    if (Child.prototype.hasOwnProperty("_init")) {
        Child.prototype._init.apply(this, arguments);
    }
  };

  // inherit
  Parent = Parent || Object;
  F = function () {};
  F.prototype = Parent.prototype;
  Child.prototype = new F();
  Child.super = Parent.prototype;
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