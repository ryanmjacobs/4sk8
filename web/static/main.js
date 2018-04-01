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
          div.innerHTML = "You are going to...." + venues.name;
      });
}
