navbar = document.getElementById("chapternav");
for (let i = 1; navbar.children.length - 1; i++) {
    navbar.children[i].href = navbar.children[i].innerHTML + ".html";
}
