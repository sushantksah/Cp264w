// This file depends on constants.js already being included
window.addEventListener( 'd2l-rubric-total-score-changed', (event) => updateGradeFromRubricChanges(event) );

function getRenderedGradeName( userId, gradeObjectId, suffix ) {
	var name = USER_PREFIX + "_" + userId + "_" + GRADE_PREFIX + "_" + gradeObjectId;
	if ( suffix ) {
		name += "_" + suffix;
	}
	return name;
}

function isControlEditDecimal( control ) {
    return control !== null && typeof (control.GetDecimal) == 'function';
}

function getRenderedGrade( userId, gradeObjectId, suffix  ) {

    var nameOrId = getRenderedGradeName(userId, gradeObjectId, suffix);
	
	if ( suffix == GRADE_SUFFIX || suffix == SCHEME_SUFFIX || suffix == COLOUR_SUFFIX ) {
		var ret = UI.GetById( nameOrId );
		if( ret ) {
			return ret;
		}
		ret = UI.GetControl( nameOrId );
		return ret ? ret.GetDomNode() : null;
	} else if ( suffix == ERR_DG_SUFFIX || suffix == GRADE_DG_SUFFIX ) {
		return UI.displayGroups.GetGroup( nameOrId );
	} else {
	    var control = UI.GetControl( nameOrId );
	    if ( isControlEditDecimal( control ) ) {
	        return control;
	    } else {
	        return UI.GetByName( nameOrId );
	    }
	}
}

function getRenderedGradeValue( userId, gradeObjectId, suffix ) {

	var renderedGrade = getRenderedGrade( userId, gradeObjectId, suffix );

	if ( renderedGrade ) {
	
		if ( isControlEditDecimal( renderedGrade ) ) {
			//numeric
			if (!renderedGrade.HasValueNoDelay()) {
				return '';
			} else {
				return renderedGrade.GetDecimal();
			}
		}
		else if ( renderedGrade.type && ( renderedGrade.type == "text" || renderedGrade.type == "hidden" )  ) {
			//textbox - trim value before returning
			return renderedGrade.value.replace(/(\s+$)|(^\s+)/g, '');
		}
		else {
			//selectlist
			return renderedGrade.GetSelectedOption().GetKey();
		}
	}
	
	//could not find rendered grade
	return "";
}

function setRenderedGradeValue( userId, gradeObjectId, val, showChange, suffix, maxDecimalPoints ) {

	var renderedGrade = getRenderedGrade( userId, gradeObjectId, suffix );

	if ( renderedGrade ) {
	
		if ( suffix == GRADE_SUFFIX || suffix == SCHEME_SUFFIX ) {
			renderedGrade.innerHTML = val;
		}
		else if (typeof (renderedGrade.GetDecimal) == 'function') {
			if (val === '') {
				renderedGrade.Clear();
			} else if( maxDecimalPoints !== undefined && maxDecimalPoints !== null ) {
				renderedGrade.SetDecimalWithNumDecimalPlaces( val, maxDecimalPoints );
			} else {
				renderedGrade.SetDecimal( val );
			}
		}
		else if ( renderedGrade.type && ( renderedGrade.type == "text" || renderedGrade.type == "hidden" ) ) {
			renderedGrade.value = val;
		}
		else {
			if ( val === '' ) {
				val = -1;
			}
			var selectOption = renderedGrade.GetOption( val ) 
			renderedGrade.SelectOption( selectOption, true );
		}
		
		if ( showChange ) {
			FormManager.ForceChange( renderedGrade );
		}
	}
}

function updateGradeFromRubricChanges( event ) {
	const rubricScore = event.detail.score;
	const rubricOutOf = event.detail.outOf;
	if (event.target && event.target.attributes) {
		const gradeObjectId = event.target.attributes['grade-object-id']?.value;
		const scoringRubricAttr = event.target.attributes['scoring-rubric'];
		const gradeContext = GradeObjIdToContext[gradeObjectId];
		if (scoringRubricAttr &&
			gradeObjectId &&
			gradeContext &&
			gradeContext.UserId &&
			gradeContext.Denom &&
			gradeContext.IsNumeric) {
			const fractionalScore = rubricScore / rubricOutOf;
			const weightedScore = fractionalScore * gradeContext.Denom;
			setRenderedGradeValue( gradeContext.UserId, gradeObjectId, weightedScore, true, null, 2 );
		}
	}
	event.stopPropagation();
}

function displayCalculatedError( userId, objectId ) {

	var errStatus = getRenderedGradeValue( userId, objectId, ERR_STATUS_SUFFIX );
	displayError( objectId, errStatus );
}

var dce = displayCalculatedError;

function clearCalculatedError( userId, objectId ) {
	getRenderedGrade( userId, objectId, ERR_DG_SUFFIX ).Hide();
	setRenderedGradeValue( userId, objectId, 0, true, ERR_STATUS_SUFFIX );
}

var cce = clearCalculatedError;

function displayError( objectId, errStatus ) {

	var termName;
	
	switch( parseInt( errStatus ) ) {
		case STATUS_OK:
		case STATUS_NULL_POINTS:
		case STATUS_NO_FORMULA:
			termName = '';
			break;
			
		case STATUS_MISSING_GRADE_ITEM:
			termName = 'Grades.Shared:FormulaErrors.errMissingGradeItem';
			break;
			
		case STATUS_DIVIDE_BY_ZERO:
			termName = 'Grades.Shared:FormulaErrors.errDivideByZero';
			break;
			
		case STATUS_OVERFLOW:
			termName = 'Grades.Shared:FormulaErrors.errOverflow';
			break;
			
		case STATUS_CIRCULAR_REFERENCE:
			termName = 'Grades.Shared:FormulaErrors.errCircularReference';
			break;
			
		case STATUS_INVALID_REFERENCE:
			termName = 'Grades.Shared:FormulaErrors.errInvalidReference';
			break;
			
		case STATUS_PARSE:
			termName = 'Grades.Shared:FormulaErrors.errSyntaxError';
			break;
			
		default:
			termName = 'Grades.Shared:FormulaErrors.errUnknown';
			break;
	}
	
	var rpcCallback = function ( rpcResponse ) {
		if( rpcResponse.GetType() == D2L.Rpc.ResponseType.Success ) {
			if( termName && termName.length > 0 ) {
				var primary = new D2L.Language.Term( termName, rpcResponse.GetResult() );
				var secondary = new D2L.Language.Term( 'Grades.Shared:FormulaErrors.errSecondary', rpcResponse.GetResult() );
				UI.Error( primary, secondary );
				
			}
		}
	}
	
	D2L.Rpc.Create( 'LookupGradeItemName', rpcCallback, '/d2l/lms/grades/controls/grade_object_render.d2l' ).Call( objectId );	
}

var der = displayError;

function ValidateFinalAdjusted( vObj, obj1Name, obj2Name, canExceed ) {

	var numerator = UI.GetControl( obj1Name );
	var denom = UI.GetControl( obj2Name );
	
	var emptyNumerator = numerator.IsEmpty();
	var emptyDenom = denom.IsEmpty();
	
	var numeratorNum = numerator.GetDecimal();
	var denomNum = denom.GetDecimal();
	
	if( emptyDenom && emptyNumerator ) {
		return true;
	}
	
	if( emptyDenom && !emptyNumerator ) {
		vObj.SetDomNode( UI.GetByName( obj1Name ) );
		vObj.SetFailureControl( UI.GetByName( obj2Name ) );
		vObj.SetFailureText( new D2L.Language.Term( 'Grades.Shared:GradeRendering.errMissingDenominator' ) );
		return false;
	}
	
	if( denomNum == 0 ) {
		vObj.SetDomNode( UI.GetByName( obj2Name ) );
		vObj.SetFailureControl( UI.GetByName( obj2Name ) );
		vObj.SetFailureText( new D2L.Language.Term( 'Grades.Shared:GradeRendering.errAdjZeroDenominator' ) );
		return false;
	}
	
	if( numeratorNum > denomNum && !canExceed ) {
		vObj.SetDomNode( UI.GetByName( obj1Name ) );
		vObj.SetFailureControl( UI.GetByName( obj1Name ) );
		vObj.SetFailureText( new D2L.Language.Term( 'Grades.Shared:GradeRendering.errCannotExceed' ) );
		return false;
	}
	
	return true;
}

var vfa = ValidateFinalAdjusted;

function droppedHelp( userId, gradeObjectId ) {

	var rpcCallback = function( rpcResponse ) {
		if( rpcResponse.GetResponseType() == D2L.Rpc.ResponseType.Success ) {
			UI.Info( new D2L.Language.Term( 'Grades.Shared:GradeRendering.jsDroppedMessage', rpcResponse.GetResult() ) );
		}
	}
	
	D2L.Rpc.Create( 'GetParentCategoryName', rpcCallback ).Call( gradeObjectId );	
}

var drh = droppedHelp;
