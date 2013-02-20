included = [
    'js/test1.js',
    'js/test2.js'
];

yepnope({
    load: included,
    complete: function () {
        main();
    }
});


function main() {
    alert(dog.color);
    alert(cat.says);
}