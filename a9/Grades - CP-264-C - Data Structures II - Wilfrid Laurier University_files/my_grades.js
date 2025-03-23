function PrintUserGrades() {
	window.print();
}

function ShowGradeObjectStatisticsDialog(objectId, userId) {
	if (!window['stats' + userId + '_' + objectId]) {
		window['stats' + userId + '_' + objectId] = new D2L.Popup();
		window['stats' + userId + '_' + objectId].bodySource = '/d2l/lms/grades/my_grades/statistics_dialog.d2l';
		window['stats' + userId + '_' + objectId].AddCloseButton(true);
		window['stats' + userId + '_' + objectId].width = 625;
		window['stats' + userId + '_' + objectId].height = 500;
	}
	window['stats' + userId + '_' + objectId].queryString = 'ou=' + Global.OrgUnitId + '&objectId=' + objectId;
	window['stats' + userId + '_' + objectId].Open();
}

function gotoFinalGradeCalculationFormula(gradeObjectId, userId) {
	showGradeListDialog(GRADE_LIST_MY_GRADES_FINAL, CloseDialogCallback, userId, gradeObjectId);
}

function gotoGradeCalculationFormula(gradeObjectId, userId) {
    showGradeListDialog(GRADE_LIST_MY_GRADES_FORMULA, CloseDialogCallback, userId, gradeObjectId);
}

function CloseDialogCallback(response) {
	if (response.GetType() != D2L.Dialog.ResponseType.Positive) {
		response.GetDialog().Close();
	}
}

function ViewActivities(objectId, userId, rubricId) {

	var dialog = new D2L.NonModalDialog();
	dialog.SetSrc( '/d2l/lms/grades/my_grades/activities_dialog.d2l' );
	dialog.SetSrcParam( 'ou', Global.OrgUnitId );
	dialog.SetSrcParam( 'objectId', objectId );
	dialog.SetSrcParam( 'userId', userId );
	if (rubricId) {
		dialog.SetSrcParam( 'rubricId', rubricId );
	}
	dialog.AddPrimaryButton( D2L.Control.Button.Type.Close );
	dialog.SetSize( Math.min( 1315, window.innerWidth - 20 ), Math.min( 700, window.innerHeight - 20) );
	dialog.Open();
}

function SetPopupTitle(title) {
	parent.popup.SetTitle(title);
}
