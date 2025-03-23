function showGradeListDialog(mode, callback, userId, objectId) {

	var dialog;

	if (mode == GRADE_LIST_MY_GRADES_FINAL || mode == GRADE_LIST_MY_GRADES_FORMULA) {

		var name;
		if (objectId !== undefined) {
			name = 'gld' + mode + '_' + userId + '_' + objectId;
		} else {
			name = 'gld' + mode + '_' + userId;
		}

		if (!window[name]) {
			window[name] = new D2L.Popup();
			window[name].bodySource = '/d2l/lms/grades/general/grade_list_dialog_view.d2l';
			window[name].height = 500;
			window[name].width = 500;
			window[name].AddCloseButton(true);
		}

		var queryString = 'ou=' + Global.OrgUnitId + '&mode=' + mode;
		if (mode == GRADE_LIST_MY_GRADES_FORMULA) {
			queryString += '&objectId=' + objectId;
		}
		if (userId !== undefined) {
		    queryString += '&userId=' + userId;
		}
		window[name].queryString = queryString;
		window[name].Open();
	} else {

		dialog = new D2L.Dialog('gradesListDialog', callback);
		dialog.SetSrc('/d2l/lms/grades/general/grade_list_dialog_view.d2l', 'DialogCallback');

		dialog.SetSrcParam('mode', mode);
		dialog.SetSrcParam('userId', userId);
		dialog.SetSize(500, 500);
		dialog.Open();
	}
}
