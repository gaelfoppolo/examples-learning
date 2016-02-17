(function() {
	if(aeListener['enum'] != null) return;

	var words = [];
	var wordsToAdd = ["first", "second", "first", "red", "blue"];
	var index = 1;

	function addWord(word) {
		document.querySelector('#ae-word-to-add').style.top = "-145px";
		document.querySelector('#ae-word-to-add').style.opacity = "0";
		setTimeout(function() {
			if(words.indexOf(wordsToAdd[index-1]) == -1) {
				words.push(wordsToAdd[index-1]);
				var e = document.createElement('div');
				e.style.opacity = 0;
				e.classList.add('ae-appear');
				e.innerHTML = (document.querySelector('#ae-words').innerHTML.length == 0 ? '':', ') + wordsToAdd[index-1];
				document.querySelector('#ae-words').appendChild(e);
				e.offsetWidth;
				e.style.opacity = 1;
			}
		}, 200);
			
		setTimeout(function() {
			
			if(wordsToAdd[index] == undefined) {
				document.querySelector('#ae-word-to-add').innerHTML = "";
				return;
			}
			document.querySelector('#ae-word-to-add').innerHTML = wordsToAdd[index++];
			document.querySelector('#ae-word-to-add').style.transition = 'none';
			document.querySelector('#ae-word-to-add').offsetWidth;
			document.querySelector('#ae-word-to-add').style.top = '0';
			document.querySelector('#ae-word-to-add').style.opacity = 1;
			document.querySelector('#ae-word-to-add').offsetWidth;
			document.querySelector('#ae-word-to-add').style.transition = 'ease 0.4s';
		}, 400);
	}

	function add() {
		addWord(wordsToAdd[index]);
	}
	
	document.addEventListener('keyup', function(e) {
		if(e.keyCode == '65' && aeListener['enum'].enabled == true) {
			add();
		}
	});

	aeListener['enum'] = {
		'disable': function() {
			aeListener['enum'].enabled = false;
		},
		'enable': function() {
			aeListener['enum'].enabled = true;
		},
		'enabled': false
	};
})();