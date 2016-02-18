(function() {
	if(aeListener['tree'] != null) return;
	var tree, lines;
	var LCAs = [
		['F', 'E', 'C', 'DF', 'CD', 'CE'],			
		['G', 'B', 'A', 'AB', 'AC', 'CD', 'DG']
	];
	var LCAIndex = 0;

	function refreshColor() {
		for(var i in tree) {
			tree[i].style.stroke = "hsl(0, 0%, 40%)";
			tree[i].style.fill = "hsl(0, 0%, 13%)";
		}
		for(var i in lines) {
			lines[i].style.stroke = "hsl(0, 0%, 40%)";
		}
	}

	function nextLCA() {
		refreshColor();
		var current = LCAs[LCAIndex++];
		tree[current[0]].style.stroke = "#42affa";
		tree[current[1]].style.stroke = "#42affa";
		tree[current[2]].style.stroke = "#42affa";
		tree[current[2]].style.fill = "#42affa";
		for(var i = 3; i < current.length; ++i) {
			lines[current[i]].style.stroke = "#42affa";
		}
	}

	function init() {
		if(tree) return;
		tree = {
			'A': document.getElementById("ae-circle-A"),
			'B': document.getElementById("ae-circle-B"),
			'C': document.getElementById("ae-circle-C"),
			'D': document.getElementById("ae-circle-D"),
			'E': document.getElementById("ae-circle-E"),
			'F': document.getElementById("ae-circle-F"),
			'G': document.getElementById("ae-circle-G")
		};

		lines = {
			'AB': document.getElementById("ae-line-AB"),
			'AC': document.getElementById("ae-line-AC"),
			'CD': document.getElementById("ae-line-CD"),
			'CE': document.getElementById("ae-line-CE"),
			'DF': document.getElementById("ae-line-DF"),
			'DG': document.getElementById("ae-line-DG")
		};
	}

	document.addEventListener('keyup', function(e) {
		if(e.keyCode == '65' && aeListener['tree'].enabled == true) { // "a"
			nextLCA();
		}
	});

	aeListener['tree'] = {
		'disable': function() {
			aeListener['tree'].enabled = false;
		},
		'enable': function() {
			aeListener['tree'].enabled = true;
			init();
		},
		'enabled': false
	};
})();