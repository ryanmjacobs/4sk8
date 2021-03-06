// Get the input field
var input = document.getElementById("submit");

// Execute a function when the user releases a key on the keyboard
input.addEventListener("keyup", function(event) {
  // Cancel the default action, if needed
  event.preventDefault();
  // Number 13 is the "Enter" key on the keyboard
  if (event.keyCode === 13) {
    // Trigger the button element with a click
    document.getElementById("submit").click();
  }
}); 

const submit = document.getElementById("submit");


submit.onclick = function() {
    const query = document.getElementById("query").value;
    console.log(query);

    fetch("http://" + window.location.host + "/query/" + query, {
        method: "POST",
    })
      .then(res => res.text())
      .then(text => {
          const venues = JSON.parse(text);
          console.log(venues);

          const div = document.getElementById("data");
	  if (venues == null) {
	      div.innerHTML = "All those places are closed at the moment. :(";
	  }
	  else if (query == "ramen" || query == "Ramen")
	      div.innerHTML = "Let's go to " + venues.name + "! :D";
	  else
	      div.innerHTML = "I guess you can go to " + venues.name + ". :/";
      });
}
