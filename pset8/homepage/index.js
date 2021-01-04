
// Asignment of element with id of main, to contain dynamic content
const mainDiv = document.getElementById("main");

// Assignment of the fruit type b checking the web address (index | pears | apples | oranges | jack fruit)
// Note: Index will be handled as all of the fruit
const fruitType = location.href.split("/").pop();

// "cloudinary" is a web application that can store images where a link to an image
//  that was uploaded can be utilized
// See: https://www.cloudinary.com
const cloudRoot = "https://res.cloudinary.com/cloud-99/image/upload/q_auto:best/c_scale,h_100/v1608955284/";

// Assign an object to store all the file names of the images that will be concatenated with
// the above "cloudRoot" URI
const fruitImages = {
    "jack-fruit":[
        "jack-fruit-white.jpg",
        "jack-fruit-tree.jpg",
        "jack-fruit-bulk.jpg"
        ],
    "oranges":[
        "orange-white.jpg",
        "orange-tree.jpg",
        "orange-bulk.jpg"
        ],
    "apples":[
        "apple-white.jpg",
        "apple-tree.jpg",
        "apple-bulk.jpg"
        ],
    "pears":[
        "pear-white.jpg",
        "pear-tree.jpg",
        "pear-bulk.jpg"
        ]
};

// This will append all the images to the "mainDiv" element on every page in this application
const appendCards = () => {

    // The tenerary operator decides if the fruit type is a key to the above "fruitImages" object
    // if a key cannot be found it then returns an array of all the fileNames rather than the file names
    // for a specific fruitType
    let arr = (Object.keys(fruitImages).includes(fruitType) ?
    fruitImages[fruitType] :
    Object.values(fruitImages).flat());

    // Append each image to <div class="main">...</div>
    arr.forEach((val) => {
            // The createFruitCard function will return a div containing
            // a img element of the expected fruit.
            mainDiv.appendChild(createFruitCard(val));
    });
};

// This function is for shortening the process of creating html elements.
const element = (tag) => document.createElement(tag);

// Expects a file name for image in refrence to "cloudRoot" and returns a card like element
//  containing the image to be appended to any element chosen.
const createFruitCard = (imageFile) => {
    let card;
    let image;
    image = element("img");
    image.src = cloudRoot + imageFile;
    image.className = "card-img img-fluid";
    card = element("div");
    card.appendChild(image);
    card.className = "card";

    return card;
};

// Call function to append cards to the webpage otherwise nothing would be shown
appendCards();