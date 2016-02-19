(function() {
	if(aeListener['generation'] != null) return;
	// animation actions		
	var actions = [];

	// svg elements
	var links;
	var examples;
	var objects;

	// model
	var m = [
		[{
			taille: 1,
			forme: 'cercle',
			couleur: 'jaune'
		}, {
			taille: 2,
			forme: 'carré',
			couleur: 'rouge'
		}, {
			taille: 5,
			forme: 'triangle',
			couleur: 'bleu'
		}],
		[{
			taille: 2,
			forme: 'cercle',
			couleur: 'jaune'
		}, {
			taille: 2,
			forme: 'rectangle',
			couleur: 'rouge'
		}],
		[{
			taille: 3,
			forme: 'cercle',
			couleur: 'rouge'
		}, {
			taille: 2,
			forme: 'trapèze',
			couleur: 'rouge'
		}, {
			taille: 4,
			forme: 'carré',
			couleur: 'vert'
		}]
	];

	// shape combination
	var shapeCombi = {
		'cercle': 'cercle',
		'trapèze': 'trapèze',
		'carré': 'carré',

		'cercle-trapèze': 'quelconque',
		'cercle-carré': 'quelconque',
		'rectangle-cercle': 'quelconque',
		'rectangle-trapèze': 'quadrilatère',
		'rectangle-carré': 'rectangle',
		'rectangle-quelconque': 'quelconque',
		'rectangle-quadrilatère': 'quadrilatère',
		'polygone-triangle': 'polygone',

		'cercle-quelconque': 'quelconque',
		'cercle-quadrilatère': 'quelconque',
		'cercle-parallelogramme': 'quelconque',
		'cercle-triangle': 'quelconque',
		'carré-quelconque': 'quelconque',
		'carré-quadrilatère': 'quadrilatère',
		'carré-parallelogramme': 'parallelogramme',
		'triangle-quelconque': 'quelconque',
		'triangle-quadrilatère': 'polygone',
		'triangle-parallelogramme': 'polygone',
		'triangle-rectangle': 'polygone'
	};

	// all solutions
	var solutions = {};

	// svg modificators
	function enableLink(ex1, obj1, ex2, obj2) {
		links['' + ex1 + obj1 + ex2 + obj2].style.strokeOpacity = 1;
	}

	function disableLink(ex1, obj1, ex2, obj2) {
		links['' + ex1 + obj1 + ex2 + obj2].style.strokeOpacity = 0;
	}

	function showExample(ex) {
		examples[''+ex].style.strokeOpacity = 1;
	}

	function hideExample(ex) {
		examples[''+ex].style.strokeOpacity = 0;
	}

	function showObject(ex, obj) {
		objects['' + ex + obj].style.strokeOpacity = 1;
	}

	function hideObject(ex, obj) {
		objects['' + ex + obj].style.strokeOpacity = 0;
	}

	// gen the right table (empty, with index and example indexes)
	// gen the empty solutions array too
	function genTable(ex) {
		var table = document.querySelector('.ae-right');
		var header = document.createElement('div');
		header.classList.add('line');
		var indexHeader = document.createElement('span');
		indexHeader.innerHTML = "indice";
		var combiHeader = document.createElement('span');
		combiHeader.innerHTML = "combinaisons";
		header.appendChild(indexHeader);
		for (var i = 0; i < ex.length; ++i) {
			(function() {
				var cur = document.createElement('span');
				cur.innerHTML = i;
				header.appendChild(cur);
			})();
		}
		header.appendChild(combiHeader);
		table.appendChild(header);

		var index = 0;
		for (var i = 0; i < ex[0].length; ++i) {
			for (var j = 0; j < ex[1].length; ++j) {
				for (var k = 0; k < ex[2].length; ++k) {
					solutions['' + i + j + k] = {
						inter: {
							min: -1,
							max: -1
						},
						color: [],
						shape: ''
					};
					(function() {
						var tr = document.createElement('div');
						tr.classList.add('line');
						tr.classList.add('ae-index-' + index);
						tr.classList.add('ae-combi-0-' + i);
						tr.classList.add('ae-combi-1-' + j);
						tr.classList.add('ae-combi-2-' + k);
						tr.innerHTML = '<span>' + index + '</span>' +
							'<span class="index ae-iex-0">' + i + '</span>' +
							'<span class="index ae-iex-1">' + j + '</span>' +
							'<span class="index ae-iex-2">' + k + '</span>' +
							'<span class="ae-combi-table"></span>';
						table.appendChild(tr);
					})();
					++index;
				}
			}
		}
	}

	// can set a background color to any column of any line of the solution
	// can set a value in the combinaison column if comment is used (must be a function returning a string)
	// and taking as arguments a string representing a solution id (ex: '021')
	function highlight(obj, columns, color, comment) {
		var selector = '';
		if (obj.index) {
			selector += ' .ae-index-' + obj.index;
		}
		if (obj.obj0) {
			selector += ' .ae-combi-0-' + obj.obj0;
		}
		if (obj.obj1) {
			selector += ' .ae-combi-1-' + obj.obj1;
		}
		if (obj.obj2) {
			selector += ' .ae-combi-2-' + obj.obj2;
		}

		selector = document.querySelectorAll(selector);
		for (var i = 0; i < selector.length; ++i) {
			var current = selector[i].querySelectorAll('span');
			for (var j = 0; j < columns.length; ++j) {
				current[columns[j]].style.backgroundColor = color;
			}
			if (comment) {
				var tmp = comment(getIndexes(selector[i]));
				if (tmp) {
					current[m.length + 1].innerHTML = tmp;
				}
			}
		}
	}

	function getIndexes(elem) {
		return (/ae-combi-0-(\d)/).exec(elem.className)[1] +
			(/ae-combi-1-(\d)/).exec(elem.className)[1] +
			(/ae-combi-2-(\d)/).exec(elem.className)[1];
	}

	// remove a highlight set with the highlight function
	function unHighlight(obj, columns) {
		highlight(obj, columns, 'transparent');
	}

	/*
	 *	add: boolean, indique si on affiche ou supprime l'action
	 *	action : {
	 *		svg: {
	 *			highlightExample: [n, ...],
	 *			highlightObject: [[ex, obj], [ex, obj], ...],
	 *			highlightLink: [[ex1, obj1, ex2, obj2], ...]
	 *		},
	 *		table: {
	 *			obj: <highlight selector>,
	 *			columns: <highlight columns>,
	 *			comment: <comment>
	 *		}
	 *	}
	 */
	function action(add, action) {
		if (action.svg) {
			if (action.svg.highlightExample) {
				for (var i = 0; i < action.svg.highlightExample.length; ++i) {
					if (add) {
						showExample(action.svg.highlightExample[i]);
					} else {
						hideExample(action.svg.highlightExample[i]);
					}
				}
			}
			if (action.svg.highlightObject) {
				for (var i = 0; i < action.svg.highlightObject.length; ++i) {
					if (add) {
						showObject(action.svg.highlightObject[i][0], action.svg.highlightObject[i][1]);
					} else {
						hideObject(action.svg.highlightObject[i][0], action.svg.highlightObject[i][1]);
					}
				}
			}
			if (action.svg.highlightLink) {
				for (var i = 0; i < action.svg.highlightLink.length; ++i) {
					if (add) {
						enableLink(action.svg.highlightLink[i][0], action.svg.highlightLink[i][1],
							action.svg.highlightLink[i][2], action.svg.highlightLink[i][3]);
					} else {
						disableLink(action.svg.highlightLink[i][0], action.svg.highlightLink[i][1],
							action.svg.highlightLink[i][2], action.svg.highlightLink[i][3]);
					}
				}
			}
		}
		if (action.table) {
			if (add) {
				if (action.table.comment) {
					highlight(action.table.obj, action.table.columns, 'hsl(0, 0%, 30%)', action.table.comment);
				} else {
					highlight(action.table.obj, action.table.columns, 'hsl(0, 0%, 30%)');
				}
			} else {
				highlight(action.table.obj, action.table.columns);
			}
		}
	}

	// attributes combination functions
	function fusionShape(shape, shape2) {
		if (shape == '') return shape2;
		for (var i in shapeCombi) {
			if (i.indexOf(shape) != -1 && i.indexOf(shape2) != -1) {
				return shapeCombi[i];
			}
		}
		alert(shape + ' + ' + shape2 + " undefined");
	}

	function fusionInter(inter, value) {
		if (inter.min == -1) return {
			min: value,
			max: value
		};
		if (value < inter.min) {
			inter.min = value;
		} else if (value > inter.max) {
			inter.max = value;
		}
		return inter;
	}

	function fusionColor(colors, color) {
		if (colors.indexOf(color) === -1) {
			colors.push(color);
		}
		return colors;
	}

	// take a solution and output a string that describes it
	function genPrint(sol) {
		var ret = "<span>Forme : </span>" + sol.shape +
			", <span>couleurs : </span>(" + sol.color + "), <span>taille : </span>[" +
			sol.inter.min + ";" + sol.inter.max + "]";
		return ret;
	}

	// make the combination of an object and a solution
	function combi(index, ex, obj) {
		solutions[index].inter = fusionInter(solutions[index].inter, m[ex][obj].taille);
		solutions[index].color = fusionColor(solutions[index].color, m[ex][obj].couleur);
		solutions[index].shape = fusionShape(solutions[index].shape, m[ex][obj].forme);
	}

	function init() {
		if(solutions['000'] !=  undefined) return;

		genSVG(document.querySelector('#first-svg-example'), 'ae-gene', SVGconfig, SVGmodel, SVGrelations);

		links = {
			'0010': document.querySelector('.ae-link-00-10'),
			'0011': document.querySelector('.ae-link-00-11'),
			'0110': document.querySelector('.ae-link-01-10'),
			'0111': document.querySelector('.ae-link-01-11'),
			'0210': document.querySelector('.ae-link-02-10'),
			'0211': document.querySelector('.ae-link-02-11'),
			'1020': document.querySelector('.ae-link-10-20'),
			'1021': document.querySelector('.ae-link-10-21'),
			'1022': document.querySelector('.ae-link-10-22'),
			'1120': document.querySelector('.ae-link-11-20'),
			'1121': document.querySelector('.ae-link-11-21'),
			'1122': document.querySelector('.ae-link-11-22')
		};
		examples = {
			'0': document.querySelector('.ae-ex-0'),
			'1': document.querySelector('.ae-ex-1'),
			'2': document.querySelector('.ae-ex-2'),
		};
		objects = {
			'00': document.querySelector('.ae-obj-00'),
			'01': document.querySelector('.ae-obj-01'),
			'02': document.querySelector('.ae-obj-02'),
			'10': document.querySelector('.ae-obj-10'),
			'11': document.querySelector('.ae-obj-11'),
			'20': document.querySelector('.ae-obj-20'),
			'21': document.querySelector('.ae-obj-21'),
			'22': document.querySelector('.ae-obj-22'),
		};

		// generate the right table and the solutions array
		genTable(m);
		console.log("table générée");


		// Génération des combinaisons et des animations
		for (var i = 2; i >= 0; --i) {
			actions.push([
				true, {
					svg: {
						highlightExample: [i]
					}
				},
				200
			]);
			for (var j = 0; j < m[i].length; ++j) {
				var c = "obj" + i;
				var o = {};
				o[c] = '' + j;

				(function(i, j) {
					actions.push([
						true, {
							svg: {
								highlightObject: [
									[i, j]
								]
							},
							table: {
								obj: o,
								columns: [i + 1],
								comment: function(indexes) {
									combi(indexes, i, j);
									return genPrint(solutions[indexes]);
								}
							}
						},
						200
					]);
				})(i, j);
				actions.push([
					false, {
						svg: {
							highlightObject: [
								[i, j]
							]
						}
					},
					1200
				]);
			}
			actions.push([
				false, {
					svg: {
						highlightExample: [i]
					}
				},
				1200
			]);
		}
	}

	var actionsIndex = 0;

	document.addEventListener('keyup', function(e) {
		if(e.keyCode == '65' && aeListener['generation'].enabled == true) {
			if (actionsIndex == actions.length) {
				return;
			}
			action(actions[actionsIndex][0], actions[actionsIndex][1]);
			++actionsIndex;
		}
	});

	aeListener['generation'] = {
		'disable': function() {
			aeListener['generation'].enabled = false;
		},
		'enable': function() {
			init();
			aeListener['generation'].enabled = true;
			console.log('initialisé');
		},
		'enabled': false
	};
})();