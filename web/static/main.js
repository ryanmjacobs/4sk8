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

    fetch("http://localhost:4848/query/" + query, {
        method: "POST",
    })
      .then(res => res.text())
      .then(text => {
          const venues = JSON.parse(text);
          console.log(venues);

          const div = document.getElementById("data");
	  if (venues == null) {
	      div.innerHTML = "All places in that criteria are closed at the moment.";
	  }
	  else
	      div.innerHTML = "You are going to " + venues.name + "!";
      });
}
