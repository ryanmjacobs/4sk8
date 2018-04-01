const submit = document.getElementById("submit");

submit.onclick = function() {
    const query = document.getElementById("query").value;
    console.log(query);

    fetch("http://localhost:4848/get?query="+query)
      .then(res => res.text())
      .then(text => {
          console.log(text);
      });
}
