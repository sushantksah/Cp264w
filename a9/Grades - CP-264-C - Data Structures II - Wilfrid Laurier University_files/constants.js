var USER_PREFIX = "u";
var GRADE_PREFIX = "g";
var NUMERATOR_SUFFIX = "n";
var DENOMINATOR_SUFFIX = "d";
var RECALCULATED_SUFFIX = "r";
var GRADE_SUFFIX = "gr";
var SCHEME_SUFFIX = "sc";
var COLOUR_SUFFIX = "c";
var ERR_DG_SUFFIX = "eDG";
var ERR_TRANSFER_DG_SUFFIX = "eTD";
var ERR_CALCULATION_DG_SUFFIX = "eCD";
var GRADE_DG_SUFFIX = "gDG";
var ERR_STATUS_SUFFIX = "eSt";
var EXEMPTION_SUFFIX = "exempt";

var KEY_SEPARATOR = '_';

//corresponds to Constants.IgnoreFinalPropertySave
var IGNORE_SAVE_ALL = 0;
var IGNORE_CALCULATED = 1;
var IGNORE_ADJUTSED = 2;
var IGNORE_RELEASED = 3;

//corresponds to querystring parameter names defined in Constants.cs
var QS_OBJECT_ID = "objectId";
var QS_OBJECT_TYPE_ID = "objectType";
var QS_SCHEME_ID = "schemeId";
var QS_FEEDBACK = "feedback";
var QS_IS_POPUP = "popup";
var QS_USER_ID = "userId";
var QS_MODE = "mode";
var QS_GRADE_ALL = "gradeAll";
var QS_CONFLICTS = "conflicts";
var QS_LOG_ID = "logId";
var QS_IS_PREVIOUS = "isPrevious";

//corresponds to Constants.GradingSystem
var GS_POINTS = 0;
var GS_WEIGHTED = 1;
var GS_FORMULA = 2;

//correspondes to Constants.GradeObjectType
var GOT_NUMERIC = 1;
var GOT_PASS_FAIL = 2;
var GOT_SELECTBOX = 3;
var GOT_TEXT = 4;
var GOT_CALCULATED = 5;
var GOT_FORMULA = 6;
var GOT_CALC_FINAL_GRADE = 7;
var GOT_ADJ_FINAL_GRADE = 8;
var GOT_CATEGORY = 9;

//corresponds to Constants.ShowFeedback
var FEEDBACK_NONE = 0;
var FEEDBACK_CREATED = 1; 
var FEEDBACK_SAVED = 2;
var FEEDBACK_REORDERED = 3;
var FEEDBACK_DELETED = 4;
var FEEDBACK_COPIED = 5;
var FEEDBACK_IMPORTED = 6;
var FEEDBACK_COURSE_INACTIVE = 14;
var FEEDBACK_COURSE_START_DATE_FUTURE = 15;
var FEEDBACK_COURSE_END_DATE_PAST = 16;

//corresponds to Constants.GradeListDialogMode
var GRADE_LIST_CALCULATED = 1;
var GRADE_LIST_ADJUSTED = 2;
var GRADE_LIST_DISPLAY_OPTIONS = 3;
var GRADE_LIST_MY_GRADES_FINAL = 4;
var GRADE_LIST_MY_GRADES_FORMULA = 5;

var STATUS_OK = 0;
var STATUS_UNKNOWN_ERR = 1;
var STATUS_DIVIDE_BY_ZERO = 2;
var STATUS_OVERFLOW = 3;
var STATUS_INVALID_REFERENCE = 4;
var STATUS_PARSE = 5;
var STATUS_CIRCULAR_REFERENCE = 6;
var STATUS_MISSING_GRADE_ITEM = 7;
var STATUS_NULL_POINTS = 8;
var STATUS_NO_FORMULA = 9;
var STATUS_FORMULA_ERROR = 10;

var SIS_EXPORT_RESULT_STATUS = 0;
var SIS_EXPORT_RESULT_REQUEST = 1;
var SIS_EXPORT_RESULT_USERID = 2;

var SAVE_BATCH_SIZE = 50;
var SAVE_BATCH_BOUNDARY_TOLERANCE = 5;

var FIELD_NUMERATOR = "Numerator";
var FIELD_DENOMINATOR = "Denominator";
var FIELD_DECIMAL_NUMERATOR = "DecimalNumerator";
var FIELD_GRADETEXT = "GradeText";
var FIELD_STATUS = "Status";
var FIELD_RELEASED = "IsReleased";
var FIELD_UPDATED = "IsUpdated";
var FIELD_PUBLIC_COMMENTS = "PublicComments";
var FIELD_PUBLIC_COMMENTS_HTML = "PublicCommentsIsHtml";
var FIELD_PRIVATE_COMMENTS = "PrivateComments";
var FIELD_PRIVATE_COMMENTS_HTML = "PrivateCommentsIsHtml";
var FIELD_EXEMPT = "Exempt";

var GRADE_USAGE_ASSOCIATION = 1;
var GRADE_USAGE_ASSOCIATION_FORMULA = 2;

var MAX_NUMERIC_VALUE = 9999999999;
var MIN_MAX_POINTS = 0.01;