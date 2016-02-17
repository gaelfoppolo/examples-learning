var inters = [5, 8, 12, 15, 2];
var index = 1;

var interA, interB;

var interCombiGen;
var interInit = 0;

(function() {
	if(interInit) return;
	interInit = 1;
	function genDash(inter, n, value) {
		if(inter.getAttribute("data-n") != undefined) {
			return;
		}
		++n;
		var dash = inter.querySelector('.dash');
		var interfill = inter.querySelector(".inter-fill");
		inter.setAttribute("data-n", n);
		inter.setAttribute("data-min", value);
		inter.setAttribute('data-max', value);
		var first = 1;
		for(var i = 0; i < n; ++i) {
			(function() {
				var elem = document.createElement('div');
				elem.className = "uni-dash";
				dash.appendChild(elem);
				if(!first) {
					elem.style.marginLeft = (inter.offsetWidth - n*3)/(n-1) + 'px';
				}
				if(i == value) {
					elem.classList.add('big');
				}
				dash.offsetWidth;
				elem.style.transition = 'ease 0.4s all';
				first = 0;
			})();
		}
		interfill.style.width = 0;
		interfill.style.left = (value+1)*(inter.offsetWidth - n*3)/(n-1) - 4 + 'px';
		interfill.offsetWidth;
		interfill.style.transition = 'ease 0.4s all';
	}

	function setInter(inter, min, max) {
		var bigs = inter.querySelectorAll('.big, .selected');
		var interfill = inter.querySelector(".inter-fill");
		var n = inter.getAttribute("data-n");
		inter.setAttribute('data-min', min);
		inter.setAttribute('data-max', max);
		for(var i = 0; i < bigs.length; ++i) {
			bigs[i].classList.remove('big');
			bigs[i].classList.remove('selected');
		}
		var all = inter.querySelectorAll('.uni-dash');
		for(var i = min+1; i < max; ++i) {
			all[i].classList.add('selected');
		}
		all[min].classList.add("big");
		all[max].classList.add("big");
		interfill.style.left = (min)*(inter.offsetWidth)/(n-1) + 'px';
		interfill.style.width = (max-min)*(inter.offsetWidth)/(n-1) + 'px';
	}

	// remove the default first bar
	function removeFirst() {
		var bigs = interA.querySelectorAll('.big, .selected');
		for(var i = 0; i < bigs.length; ++i) {
			bigs[i].classList.remove('big');
			bigs[i].classList.remove('selected');
		}
	}

	function next() {
		interB.style.top = "-125px";
		interB.style.opacity = "0";
		setTimeout(function() {
			setInter(interA, Math.min(inters[index-1], parseInt(interA.getAttribute('data-min'))), Math.max(inters[index-1], parseInt(interA.getAttribute('data-max'))));
		}, 200);

		setTimeout(function() {
			interB.style.transition = 'none';
			interB.offsetWidth;
			var current = inters[index++];
			setInter(interB, current, current);
			interB.style.top = '80px';
			interB.style.opacity = 1;
			interB.offsetWidth;
			interB.style.transition = 'ease 0.4s';
		}, 400);
	}

	document.addEventListener('keyup', function(e) {
		if(e.keyCode == '13') {
			next();
		}
	});

	interCombiGen = function() {
		interA = document.querySelector('#inter-1');
		interB = document.querySelector('#inter-2');
		genDash(interA, 20, 5);
		genDash(interB, 20, 5);
		removeFirst();
	}
})();