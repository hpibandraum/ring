
function ringTheBell() {
   var xhttp;
   if (window.XMLHttpRequest) {
     xhttp = new XMLHttpRequest();
   } else {
     xhttp = new ActiveXObject("Microsoft.XMLHTTP");
   }
   
  xhttp.onreadystatechange = function() {
    if (xhttp.readyState == 4 && xhttp.status == 200) {
      alert(xhttp.responseText);
    }
  };
  xhttp.open("POST", "https://api.particle.io/v1/devices/25001c000247343138333038/bell?access_token=a2882f03a5972ba19227709f65c0f49d5091d9ba", true);
  xhttp.send();
}