(function() {
	if(aeListener['indice'] != null) return;

	var isInit = false;

	function init() {
		if(isInit) return;
		isInit = true;
		var myDisplay = new AEdisplay('indice-svg', SVGmodel, SVGrelations, SVGconfig);
		var stack = null;

		myDisplay.linkElement(document.querySelector('#ae-indice-cont'));
		myDisplay.prepareSvg();
		myDisplay.init();

		myDisplay.addAction({
			'svg': {
				'showObject': [[0, 1]],
			}
		});
		myDisplay.addAction({
			'svg': {
				'showObject': [[1, 0]],
			}
		});
		myDisplay.addAction({
			'svg': {
				'showObject': [[2, 2]],
			}
		});

		document.addEventListener('keyup', function(e) {
			if(e.keyCode == '65' && aeListener['indice'].enabled == true) {
				myDisplay.nextStep();
			}
		});
	}

	aeListener['indice'] = {
		'disable': function() {
			aeListener['indice'].enabled = false;
		},
		'enable': function() {
			init();
			aeListener['indice'].enabled = true;
		},
		'enabled': false
	};
})();