/*global yepnope:true, APP:true */

var included = [
    'js/test1.js',
    'js/test2.js',
    'js/Klass.js'
];


function main() {
    'use strict';
    alert(dog.color);
    alert(cat.says);
}

yepnope({
    load: included,
    complete: function () {
        'use strict';
        main();
    }
    });
