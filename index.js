
function ringTheBell() {
  var knopka = document.getElementById("knopka");
  var xhttp;
  if (window.XMLHttpRequest) {
   xhttp = new XMLHttpRequest();
  } else {
   xhttp = new ActiveXObject("Microsoft.XMLHTTP");
  }
   
  xhttp.onreadystatechange = function() {
    if (xhttp.readyState == 4 && xhttp.status == 200) {
      var response = JSON.parse(xhttp.responseText);
      var secondsToWait = response.return_value;
      if (secondsToWait === parseInt(secondsToWait, 10)) {
        // check for integer from http://stackoverflow.com/a/14636652/1320237
        knopka.innerHTML= "Ringing...";
        setTimeout(function() {
            knopka.innerHTML= "";
          }, secondsToWait * 1000);
      } 
    } else {
      knopka.innerHTML= "Error - plug it in!";
    }
  };
  knopka.innerHTML = "Sending...";
  xhttp.open("POST", "https://api.particle.io/v1/devices/25001c000247343138333038/bell?access_token=a2882f03a5972ba19227709f65c0f49d5091d9ba", true);
  xhttp.send();
}

