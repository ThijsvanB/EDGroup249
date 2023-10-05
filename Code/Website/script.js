async function submitPlant() {
	document.getElementById("details").innerHTML = "Loading...";
	
	var key = 'sk-PCgL65070ca5448482160';

	var query = 'https://perenual.com/api/species-list?key=' + key + '&q=' + document.getElementById("plantname").value;
	
	var requestOptions = {
		method: '',
		redirect: 'follow'
	};
	
	let obj1, obj2;
	
	const res1 = await fetch(query);
	obj1 = await res1.json();
	
	var textout = "Plants: <br><br>"
	var results = 0;
	
	for(let i = 0; i < Math.min(obj1.data.length, 2); i++) {
		var query2 = 'https://perenual.com/api/species/details/' + obj1.data[i].id + '?key=' + key;
	
		results += 1;
	
		const res2 = await fetch(query2)
			.catch(error => {console.log('error', error); results -= 1;});
			
		obj2 = await res2.json();
		console.log(typeof obj2);
		console.log(Object.keys(obj2));
		console.log(obj2.common_name);
		console.log(obj2.watering);
		
		var newButton = document.createElement('button');
		newButton.textContent = "Select";
		newButton.addEventListener('click', clickHandler, false);
		newButton.name = obj2.common_name;
		document.getElementById("Selection").appendChild(newButton);
		
		var a = document.createElement('a');
		var link = document.createTextNode(obj2.common_name);
		a.appendChild(link);
		a.title = "Link";
		a.href = "https://perenual.com/plant-species-database-search-finder/species/" + obj2.id.toString();
		document.getElementById("Selection").appendChild(a);
		
		var breakline = document.createElement('br');
		document.getElementById("Selection").append(breakline);
		
		document.getElementById("details").innerHTML = "Select your plant: (you can click on the link to see more details)";
	}
	
	if(results == 0) {
		document.getElementById("details").innerHTML = "No results found";
	}
}

function clickHandler(evt) {
	var x = document.getElementById("Result");	
	while(x.firstChild) {
		x.removeChild(x.lastChild);
	}
	
	var p = document.createElement('p');
	var textP = document.createTextNode("Selected: " + evt.currentTarget.name);
	p.appendChild(textP);
	x.appendChild(p);
	
	x.style.display = "block";
}

//Abies Fraseri