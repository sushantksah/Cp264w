// grades.js
// - This page is included in the "GradesPage" base page

// Specific navigation methods

function gotoEnterGrades() {
	navigateTo("/d2l/lms/grades/admin/enter/user_list_view.d2l");		
}

function gotoManageGrades() {
	navigateTo("/d2l/lms/grades/admin/manage/gradeslist.d2l");
}

function gotoGradesSettings() {
	navigateTo("/d2l/lms/grades/admin/settings/personal_display_options.d2l");
}	

function gotoGradesSchemes() {
	navigateTo("/d2l/lms/grades/admin/schemes/schemes_list.d2l");
}

function gotoManageGradeSchemes() {
	gotoGradesSchemes();
}

function gotoSetupWizard() {
	navigateTo("/d2l/lms/grades/admin/settings/wizard_options.d2l");
}	

// Generic navigation methods

function navigateTo( location ) {
	navigateToExAction( location, null, null, null );
}

function navigateToObject( location, gradeObjectId ) {
	navigateToExAction( location, 'objectId', gradeObjectId, null );
}

function navigateToEx( location, paramName, paramValue ) {
	navigateToExAction( location, paramName, paramValue, null );
}

function navigateToExAction( location, paramName, paramValue, action ) {

	var ni = new D2L.NavInfo();
	ni.navigation = location;
	if( action ) {
		ni.action = action;
	}
	ni.SetParam( paramName, paramValue );
	Nav.Go( ni );
}


// Common functions

function IsGradeItem( got ) {
	switch( got ) {
		case GOT_NUMERIC:
		case GOT_PASS_FAIL:
		case GOT_SELECTBOX:
		case GOT_TEXT:
		case GOT_CALCULATED:
		case GOT_FORMULA:
			return true;
			break;
	}
	return false;
}

function showSaveDialog( callback, message1, message2 ) {
	
	if ( message2 === undefined ) {
		message2 = '';
	}

	var dialog = new D2L.Dialog.Confirm( 'SaveConfirmDialog',callback, message1, message2 );
	if( isStickyHeadersEnabled() ) {
		// dialog.Open() positions the dialog incorrectly when sticky headers are 
		// enabled. Since we also need to return the dialog, we set the position in
		// the timeout.
		setTimeout(function() {
			dialog.SetPosX( ( window.innerWidth / 2 ) - ( dialog.GetWidth() / 2 ) );
		}, 50);
	}
	return dialog.Open();
}

function isStickyHeadersEnabled() {
	return D2L
		&& D2L.LP
		&& D2L.LP.Web
		&& D2L.LP.Web.UI
		&& D2L.LP.Web.UI.Desktop
		&& D2L.LP.Web.UI.Desktop.Controls
		&& D2L.LP.Web.UI.Desktop.Controls.StickyHeaders
		&& D2L.LP.Web.UI.Desktop.Controls.StickyHeaders.isEnabled();
}
