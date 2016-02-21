(function() {
	if(aeListener['relation'] != null) return;

	var isInit = false;

	function init() {
		if(isInit) return;
		isInit = true;
		var myDisplay = new AEdisplay('relation-svg', SVGmodel, SVGrelations, SVGconfig);
		var stack = null;

		myDisplay.linkElement(document.querySelector('#ae-relation-cont'));
		myDisplay.prepareSvg();
		myDisplay.init();

		myDisplay.addAction({
			'svg': {
				'showObject': [[0, 0], [1, 0], [2, 0]],
			}
		});
		myDisplay.addAction({
			'svg': {
				'showObject': [[0, 1], [1, 1], [2, 1]],
				'color': '#42affa'
			}
		});

		document.addEventListener('keyup', function(e) {
			if(e.keyCode == '65' && aeListener['relation'].enabled == true) {
				myDisplay.nextStep();
			}
		});
	}

	aeListener['relation'] = {
		'disable': function() {
			aeListener['relation'].enabled = false;
		},
		'enable': function() {
			init();
			aeListener['relation'].enabled = true;
		},
		'enabled': false
	};
})();