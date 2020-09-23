webpackJsonp([0],[
/* 0 */,
/* 1 */,
/* 2 */,
/* 3 */,
/* 4 */,
/* 5 */,
/* 6 */,
/* 7 */,
/* 8 */,
/* 9 */,
/* 10 */,
/* 11 */,
/* 12 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
/* harmony export (immutable) */ __webpack_exports__["b"] = domain;
/* harmony export (immutable) */ __webpack_exports__["a"] = count;
/* harmony export (immutable) */ __webpack_exports__["c"] = prettyDate;
/* harmony export (immutable) */ __webpack_exports__["d"] = pluralize;
var urlParser = document.createElement('a');

function domain(url) {
  urlParser.href = url;
  return urlParser.hostname;
}

function count(arr) {
  return arr.length;
}

function prettyDate(date) {
  var a = new Date(date);
  return a.toDateString();
}

function pluralize(time, label) {
  if (time === 1) {
    return time + label;
  }

  return time + label + 's';
}

/***/ }),
/* 13 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__components_Dash_vue__ = __webpack_require__(92);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__components_Dash_vue___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_0__components_Dash_vue__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__components_Login_vue__ = __webpack_require__(93);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__components_Login_vue___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_1__components_Login_vue__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__components_views_DeviceConfig_vue__ = __webpack_require__(105);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__components_views_DeviceConfig_vue___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_2__components_views_DeviceConfig_vue__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__components_views_UpstreamConfig_vue__ = __webpack_require__(114);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__components_views_UpstreamConfig_vue___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_3__components_views_UpstreamConfig_vue__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__components_views_Meterconfig_vue__ = __webpack_require__(107);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__components_views_Meterconfig_vue___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_4__components_views_Meterconfig_vue__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_5__components_views_ParamConfig_vue__ = __webpack_require__(109);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_5__components_views_ParamConfig_vue___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_5__components_views_ParamConfig_vue__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_6__components_views_Status_vue__ = __webpack_require__(112);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_6__components_views_Status_vue___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_6__components_views_Status_vue__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_7__components_views_ViewData_vue__ = __webpack_require__(115);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_7__components_views_ViewData_vue___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_7__components_views_ViewData_vue__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_8__components_views_OnDemand_vue__ = __webpack_require__(108);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_8__components_views_OnDemand_vue___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_8__components_views_OnDemand_vue__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_9__components_views_Diagnostic_vue__ = __webpack_require__(106);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_9__components_views_Diagnostic_vue___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_9__components_views_Diagnostic_vue__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_10__components_views_Transferfirmware_vue__ = __webpack_require__(113);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_10__components_views_Transferfirmware_vue___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_10__components_views_Transferfirmware_vue__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_11__components_views_Servicehistory_vue__ = __webpack_require__(111);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_11__components_views_Servicehistory_vue___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_11__components_views_Servicehistory_vue__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_12__components_views_SaveandApply_vue__ = __webpack_require__(110);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_12__components_views_SaveandApply_vue___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_12__components_views_SaveandApply_vue__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_13__components_views_Changepassword_vue__ = __webpack_require__(104);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_13__components_views_Changepassword_vue___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_13__components_views_Changepassword_vue__);
















var routes = [{
    path: '/',
    name: 'Login',
    component: __WEBPACK_IMPORTED_MODULE_1__components_Login_vue___default.a
}, {
    path: '/dcu',
    component: __WEBPACK_IMPORTED_MODULE_0__components_Dash_vue___default.a,
    children: [{
        path: 'deviceconfig',
        alias: '',
        component: __WEBPACK_IMPORTED_MODULE_2__components_views_DeviceConfig_vue___default.a,
        name: 'Device',
        meta: { description: 'Configuration' }
    }, {
        path: 'upstreamconfig',
        alias: '',
        component: __WEBPACK_IMPORTED_MODULE_3__components_views_UpstreamConfig_vue___default.a,
        name: 'Upstream',
        meta: { description: 'Configuration' }
    }, {
        path: 'meterconfig',
        alias: '',
        component: __WEBPACK_IMPORTED_MODULE_4__components_views_Meterconfig_vue___default.a,
        name: 'Meter',
        meta: { description: 'Configuration' }
    }, {
        path: 'paramsconfig',
        alias: '',
        component: __WEBPACK_IMPORTED_MODULE_5__components_views_ParamConfig_vue___default.a,
        name: 'Parameter',
        meta: { description: 'Configuration' }
    }, {
        path: 'status',
        alias: '',
        component: __WEBPACK_IMPORTED_MODULE_6__components_views_Status_vue___default.a,
        name: 'Status',
        meta: { description: '' }
    }, {
        path: 'viewdata',
        alias: '',
        component: __WEBPACK_IMPORTED_MODULE_7__components_views_ViewData_vue___default.a,
        name: 'View Data',
        meta: { description: '' }
    }, {
        path: 'ondemand',
        alias: '',
        component: __WEBPACK_IMPORTED_MODULE_8__components_views_OnDemand_vue___default.a,
        name: 'On Demand ',
        meta: { description: 'Command' }
    }, {
        path: 'diagnostic',
        alias: '',
        component: __WEBPACK_IMPORTED_MODULE_9__components_views_Diagnostic_vue___default.a,
        name: 'Diagnostics ',
        meta: { description: '' }
    }, {
        path: 'transferfirmware',
        alias: '',
        component: __WEBPACK_IMPORTED_MODULE_10__components_views_Transferfirmware_vue___default.a,
        name: 'Transfer Firmware',
        meta: { description: '' }
    }, {
        path: 'changepassword',
        alias: '',
        component: __WEBPACK_IMPORTED_MODULE_13__components_views_Changepassword_vue___default.a,
        name: 'Change password',
        meta: { description: '' }
    }, {
        path: 'servicehistory',
        alias: '',
        component: __WEBPACK_IMPORTED_MODULE_11__components_views_Servicehistory_vue___default.a,
        name: 'Service History',
        meta: { description: '' }
    }, {
        path: 'saveandapply',
        alias: '',
        component: __WEBPACK_IMPORTED_MODULE_12__components_views_SaveandApply_vue___default.a,
        name: 'Save and Apply',
        meta: { description: '' }
    }]
}];

/* harmony default export */ __webpack_exports__["a"] = (routes);

/***/ }),
/* 14 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_vue__ = __webpack_require__(4);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_vuex__ = __webpack_require__(5);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__state__ = __webpack_require__(27);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__actions__ = __webpack_require__(25);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__mutations__ = __webpack_require__(26);






__WEBPACK_IMPORTED_MODULE_0_vue__["default"].use(__WEBPACK_IMPORTED_MODULE_1_vuex__["a" /* default */]);

/* harmony default export */ __webpack_exports__["a"] = (new __WEBPACK_IMPORTED_MODULE_1_vuex__["a" /* default */].Store({
  state: __WEBPACK_IMPORTED_MODULE_2__state__["a" /* default */],
  actions: __WEBPACK_IMPORTED_MODULE_3__actions__["a" /* default */],
  mutations: __WEBPACK_IMPORTED_MODULE_4__mutations__["a" /* default */]
}));

/***/ }),
/* 15 */,
/* 16 */,
/* 17 */,
/* 18 */,
/* 19 */
/***/ (function(module, exports, __webpack_require__) {

var Component = __webpack_require__(0)(
  /* script */
  __webpack_require__(28),
  /* template */
  __webpack_require__(116),
  /* scopeId */
  null,
  /* cssModules */
  null
)

module.exports = Component.exports


/***/ }),
/* 20 */,
/* 21 */,
/* 22 */,
/* 23 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
/* harmony default export */ __webpack_exports__["a"] = ({
  serverURI: '',
  fixedLayout: false,
  hideLogoOnMobile: false
});

/***/ }),
/* 24 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
Object.defineProperty(__webpack_exports__, "__esModule", { value: true });
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "bus", function() { return bus; });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_object_define_properties__ = __webpack_require__(15);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_object_define_properties___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_object_define_properties__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_es6_promise_auto__ = __webpack_require__(16);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_es6_promise_auto___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_1_es6_promise_auto__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2_vue__ = __webpack_require__(4);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3_vue_router__ = __webpack_require__(20);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4_vuex_router_sync__ = __webpack_require__(22);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4_vuex_router_sync___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_4_vuex_router_sync__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_5__routes__ = __webpack_require__(13);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_6__store__ = __webpack_require__(14);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_7_vue_sessionstorage__ = __webpack_require__(21);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_7_vue_sessionstorage___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_7_vue_sessionstorage__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_8__filters__ = __webpack_require__(12);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_9_vue_js_modal__ = __webpack_require__(18);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_9_vue_js_modal___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_9_vue_js_modal__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_10_crip_vue_notice__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_10_crip_vue_notice___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_10_crip_vue_notice__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_11_vue_blockui__ = __webpack_require__(17);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_12__components_App_vue__ = __webpack_require__(19);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_12__components_App_vue___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_12__components_App_vue__);






var bus = new __WEBPACK_IMPORTED_MODULE_2_vue__["default"]();












__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_object_define_properties___default()(__WEBPACK_IMPORTED_MODULE_2_vue__["default"].prototype, {
    $bus: {
        get: function get() {
            return EventBus;
        }
    }
});

__WEBPACK_IMPORTED_MODULE_2_vue__["default"].filter('count', __WEBPACK_IMPORTED_MODULE_8__filters__["a" /* count */]);
__WEBPACK_IMPORTED_MODULE_2_vue__["default"].filter('domain', __WEBPACK_IMPORTED_MODULE_8__filters__["b" /* domain */]);
__WEBPACK_IMPORTED_MODULE_2_vue__["default"].filter('prettyDate', __WEBPACK_IMPORTED_MODULE_8__filters__["c" /* prettyDate */]);
__WEBPACK_IMPORTED_MODULE_2_vue__["default"].filter('pluralize', __WEBPACK_IMPORTED_MODULE_8__filters__["d" /* pluralize */]);
__WEBPACK_IMPORTED_MODULE_2_vue__["default"].use(__WEBPACK_IMPORTED_MODULE_11_vue_blockui__["default"]);
__WEBPACK_IMPORTED_MODULE_2_vue__["default"].use(__WEBPACK_IMPORTED_MODULE_9_vue_js_modal___default.a);
__WEBPACK_IMPORTED_MODULE_2_vue__["default"].use(__WEBPACK_IMPORTED_MODULE_3_vue_router__["a" /* default */]);
__WEBPACK_IMPORTED_MODULE_2_vue__["default"].use(__WEBPACK_IMPORTED_MODULE_7_vue_sessionstorage___default.a);
__WEBPACK_IMPORTED_MODULE_2_vue__["default"].use(__WEBPACK_IMPORTED_MODULE_10_crip_vue_notice___default.a);

var router = new __WEBPACK_IMPORTED_MODULE_3_vue_router__["a" /* default */]({
    routes: __WEBPACK_IMPORTED_MODULE_5__routes__["a" /* default */],

    linkExactActiveClass: 'active',
    scrollBehavior: function scrollBehavior(to, from, savedPosition) {
        return savedPosition || { x: 0, y: 0 };
    }
});

router.beforeEach(function (to, from, next) {
    if (to.matched.some(function (record) {
        return record.meta.requiresAuth;
    }) && (!router.app.$store.state.token || router.app.$store.state.token === 'null')) {
        window.console.log('Not authenticated');
        next({
            path: '/login',
            query: { redirect: to.fullPath }
        });
    } else {
        next();
    }
});

__webpack_require__.i(__WEBPACK_IMPORTED_MODULE_4_vuex_router_sync__["sync"])(__WEBPACK_IMPORTED_MODULE_6__store__["a" /* default */], router);

if (window.localStorage) {
    var localUserString = window.localStorage.getItem('user') || 'null';
    var localUser = JSON.parse(localUserString);
    if (localUser && __WEBPACK_IMPORTED_MODULE_6__store__["a" /* default */].state.user !== localUser) {
        __WEBPACK_IMPORTED_MODULE_6__store__["a" /* default */].commit('SET_USER', localUser);
        __WEBPACK_IMPORTED_MODULE_6__store__["a" /* default */].commit('SET_TOKEN', window.localStorage.getItem('token'));
    }
}

__WEBPACK_IMPORTED_MODULE_2_vue__["default"].rootUrl = __WEBPACK_IMPORTED_MODULE_2_vue__["default"].prototype.rootUrl = '/';
__WEBPACK_IMPORTED_MODULE_2_vue__["default"].webSocketUrl = __WEBPACK_IMPORTED_MODULE_2_vue__["default"].prototype.webSocketUrl = 'ws://' + location.hostname + ':7890/';

new __WEBPACK_IMPORTED_MODULE_2_vue__["default"]({
    el: '#root',
    router: router,
    store: __WEBPACK_IMPORTED_MODULE_6__store__["a" /* default */],
    render: function render(h) {
        return h(__WEBPACK_IMPORTED_MODULE_12__components_App_vue___default.a);
    }
});

/***/ }),
/* 25 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
/* harmony default export */ __webpack_exports__["a"] = ({});

/***/ }),
/* 26 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
/* harmony default export */ __webpack_exports__["a"] = ({
  TOGGLE_LOADING: function TOGGLE_LOADING(state) {
    state.callingAPI = !state.callingAPI;
  },
  TOGGLE_SEARCHING: function TOGGLE_SEARCHING(state) {
    state.searching = state.searching === '' ? 'loading' : '';
  },
  SET_USER: function SET_USER(state, user) {
    state.user = user;
  },
  SET_TOKEN: function SET_TOKEN(state, token) {
    state.token = token;
  }
});

/***/ }),
/* 27 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
/* harmony default export */ __webpack_exports__["a"] = ({
  callingAPI: false,
  searching: '',
  serverURI: 'http://10.110.1.136:8080',
  user: null,
  token: null,
  userInfo: {
    messages: [{
      id: 1,
      title: 'Support Team',
      body: 'Why not consider this a test message?',
      createdAt: '17 min ago'
    }],
    notifications: [{
      id: 1,
      title: 'Birthday Reminder',
      body: 'Today is Brians birthday.',
      createdAt: 'just now',
      readAt: null
    }, {
      id: 2,
      title: 'Bank Holiday in London',
      body: 'Our office in London has a bank holiday today. Do not expect them to answer the phone.',
      createdAt: '4 hours ago',
      readAt: null
    }, {
      id: 3,
      title: 'Birthday Reminder',
      body: 'Today is Christians birthday.',
      createdAt: '27 days ago',
      readAt: '2018-08-12 00:00:00'
    }, {
      id: 4,
      title: 'Birthday Reminder',
      body: 'Today is Tanjas birthday.',
      createdAt: '29 days ago',
      readAt: '2018-08-12 00:00:00'
    }, {
      id: 5,
      title: 'Sales Bonus received',
      body: 'You received your monthly sales bonus of 3%. This month you made $2,700 extra!',
      createdAt: '7 hours ago',
      readAt: null
    }],
    tasks: []
  }
});

/***/ }),
/* 28 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
Object.defineProperty(__webpack_exports__, "__esModule", { value: true });


/* harmony default export */ __webpack_exports__["default"] = ({
  name: 'App',
  data: function data() {
    return {
      section: 'Head'
    };
  },

  methods: {
    logout: function logout() {
      this.$store.commit('SET_USER', null);
      this.$store.commit('SET_TOKEN', null);

      if (window.localStorage) {
        window.localStorage.setItem('user', null);
        window.localStorage.setItem('token', null);
      }

      this.$router.push('/login');
    }
  }
});

/***/ }),
/* 29 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
Object.defineProperty(__webpack_exports__, "__esModule", { value: true });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__config__ = __webpack_require__(23);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__layout_DashFooter__ = __webpack_require__(94);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__layout_DashFooter___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_1__layout_DashFooter__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__layout_DashHeader__ = __webpack_require__(95);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__layout_DashHeader___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_2__layout_DashHeader__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__layout_Sidebar__ = __webpack_require__(100);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__layout_Sidebar___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_3__layout_Sidebar__);







/* harmony default export */ __webpack_exports__["default"] = ({
  name: 'Dash',
  components: {
    DashFooter: __WEBPACK_IMPORTED_MODULE_1__layout_DashFooter___default.a,
    DashHeader: __WEBPACK_IMPORTED_MODULE_2__layout_DashHeader___default.a,
    Sidebar: __WEBPACK_IMPORTED_MODULE_3__layout_Sidebar___default.a
  },
  data: function data() {
    return {
      classes: {
        fixed_layout: __WEBPACK_IMPORTED_MODULE_0__config__["a" /* default */].fixedLayout,
        hide_logo: __WEBPACK_IMPORTED_MODULE_0__config__["a" /* default */].hideLogoOnMobile
      }
    };
  },
  computed: {},
  methods: {}
});

/***/ }),
/* 30 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
Object.defineProperty(__webpack_exports__, "__esModule", { value: true });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify__ = __webpack_require__(3);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_crip_vue_notice__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_crip_vue_notice___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_1_crip_vue_notice__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2_vue_element_loading__ = __webpack_require__(2);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2_vue_element_loading___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_2_vue_element_loading__);




/* harmony default export */ __webpack_exports__["default"] = ({
	name: "Login",
	components: {
		CripNotice: __WEBPACK_IMPORTED_MODULE_1_crip_vue_notice___default.a,
		VueElementLoading: __WEBPACK_IMPORTED_MODULE_2_vue_element_loading___default.a
	},
	data: function data() {
		return {
			section: "Login",
			isLoading: false,
			fullPage: true,
			ducUserNameTXT: "",
			ducPasswordTXT: "",
			responseTXT: "",
			userrole: "",
			get_GenconfigJSON: '',
			get_UpstreamconfigJSON: '',
			get_DlmsMeterconfigSON: '',
			get_MasterINSTJSON: '',
			get_MasterLSJSON: '',
			get_MasterMNJSON: '',
			get_MasterEVENTJSON: '',
			get_MasterBILLJSON: '',
			get_SelectedINSTJSON: '',
			get_SelectedLSJSON: '',
			get_SelectedMNJSON: '',
			get_SelectedEVENTJSON: '',
			get_SelectedBILLJSON: '',
			checkstatus: '',
			checkwebsocket: false
		};
	},

	mounted: function mounted() {},
	created: function created() {
		this.$session.set("loginsession", "");
	},
	destroyed: function destroyed() {
		if (this.checkwebsocket) {
			this.ws.close();
		}
	},
	methods: {
		loginAction: function loginAction() {
			var _this = this;

			var RespData = "";
			try {
				if (this.ducUserNameTXT == 'admin' && this.ducPasswordTXT == 'softel') {
					this.isLoading = true;
					var randomval = Math.floor(1000 + Math.random() * 9000);
					this.$session.set("loginsession", "Login success!");
					this.$session.set("UserRole", this.userrole);
					this.ws = new WebSocket(this.webSocketUrl);
					this.ws.onopen = function (e) {
						_this.checkwebsocket = true;
						var commdObj1 = { "TYPE": "CMD_MESSAGE", "SEQ_NUM": Math.floor(1000 + Math.random() * 9000).toString(), "CMD_TYPE": "GET_GEN_CONFIG" };
						_this.ws.send(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(commdObj1));
						var commdObj2 = { "TYPE": "CMD_MESSAGE", "SEQ_NUM": Math.floor(1000 + Math.random() * 9000).toString(), "CMD_TYPE": "GET_UPSTREAM_CONFIG" };
						_this.ws.send(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(commdObj2));
						var commdObj3 = { "TYPE": "CMD_MESSAGE", "SEQ_NUM": Math.floor(1000 + Math.random() * 9000).toString(), "CMD_TYPE": "GET_DLMS_CONFIG" };
						_this.ws.send(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(commdObj3));
						var commdObj4 = { "TYPE": "CMD_MESSAGE", "SEQ_NUM": Math.floor(1000 + Math.random() * 9000).toString(), "CMD_TYPE": "GET_DLMS_INST_MAST_PARAM_LIST" };
						_this.ws.send(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(commdObj4));
						var commdObj5 = { "TYPE": "CMD_MESSAGE", "SEQ_NUM": Math.floor(1000 + Math.random() * 9000).toString(), "CMD_TYPE": "GET_DLMS_LS_MAST_PARAM_LIST" };
						_this.ws.send(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(commdObj5));
						var commdObj6 = { "TYPE": "CMD_MESSAGE", "SEQ_NUM": Math.floor(1000 + Math.random() * 9000).toString(), "CMD_TYPE": "GET_DLMS_MN_MAST_PARAM_LIST" };
						_this.ws.send(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(commdObj6));
						var commdObj7 = { "TYPE": "CMD_MESSAGE", "SEQ_NUM": Math.floor(1000 + Math.random() * 9000).toString(), "CMD_TYPE": "GET_DLMS_EVENT_MAST_PARAM_LIST" };
						_this.ws.send(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(commdObj7));
						var commdObj8 = { "TYPE": "CMD_MESSAGE", "SEQ_NUM": Math.floor(1000 + Math.random() * 9000).toString(), "CMD_TYPE": "GET_DLMS_BILL_MAST_PARAM_LIST" };
						_this.ws.send(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(commdObj8));
						var commdObj9 = { "TYPE": "CMD_MESSAGE", "SEQ_NUM": Math.floor(1000 + Math.random() * 9000).toString(), "CMD_TYPE": "GET_DLMS_INST_PARAM_CONFIG" };
						_this.ws.send(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(commdObj9));
						var commdObj10 = { "TYPE": "CMD_MESSAGE", "SEQ_NUM": Math.floor(1000 + Math.random() * 9000).toString(), "CMD_TYPE": "GET_DLMS_LS_PARAM_CONFIG" };
						_this.ws.send(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(commdObj10));
						var commdObj11 = { "TYPE": "CMD_MESSAGE", "SEQ_NUM": Math.floor(1000 + Math.random() * 9000).toString(), "CMD_TYPE": "GET_DLMS_MN_PARAM_CONFIG" };
						_this.ws.send(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(commdObj11));
						var commdObj12 = { "TYPE": "CMD_MESSAGE", "SEQ_NUM": Math.floor(1000 + Math.random() * 9000).toString(), "CMD_TYPE": "GET_DLMS_EVENT_PARAM_CONFIG" };
						_this.ws.send(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(commdObj12));
						var commdObj13 = { "TYPE": "CMD_MESSAGE", "SEQ_NUM": Math.floor(1000 + Math.random() * 9000).toString(), "CMD_TYPE": "GET_DLMS_BILL_PARAM_CONFIG" };
						_this.ws.send(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(commdObj13));
					};
					this.ws.onmessage = function (e) {
						try {
							if (e.data.length == 4096) RespData = RespData + e.data;else {
								RespData = RespData + e.data;
								try {
									var split_char = RespData.split('!');
									var count = split_char.length - 1;
									for (var idx = 0; idx < count; idx++) {
										console.log("websocket:msg::" + __WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(split_char[idx]));
										var websocketBody = JSON.parse(split_char[idx]);
										RespData = '';
										console.log("correct data");
										console.log("websocket:msg::" + __WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(websocketBody));

										if (websocketBody.TYPE == "GET_GEN_CONFIG") {
											_this.get_GenconfigJSON = websocketBody;
											_this.$session.set("get_GenconfigJSON", _this.get_GenconfigJSON);
											_this.$session.set("get_copy_GenconfigJSON", _this.get_GenconfigJSON);
										} else if (websocketBody.TYPE == "GET_UPSTREAM_CONFIG") {
											_this.get_UpstreamconfigJSON = websocketBody;
											_this.$session.set("get_UpstreamconfigJSON", _this.get_UpstreamconfigJSON);
											_this.$session.set("get_copy_UpstreamconfigJSON", _this.get_UpstreamconfigJSON);
										} else if (websocketBody.TYPE == "GET_DLMS_CONFIG") {
											_this.get_DlmsMeterconfigSON = websocketBody;
											_this.$session.set("get_DlmsMeterconfigSON", _this.get_DlmsMeterconfigSON);
											_this.$session.set("get_copy_DlmsMeterconfigSON", _this.get_DlmsMeterconfigSON);
										} else if (websocketBody.TYPE == "GET_DLMS_INST_MAST_PARAM_LIST") {
											_this.get_MasterINSTJSON = websocketBody;
											_this.$session.set("get_MasterINSTJSON", _this.get_MasterINSTJSON);
											_this.$session.set("get_copy_MasterINSTJSON", _this.get_MasterINSTJSON);
										} else if (websocketBody.TYPE == "GET_DLMS_LS_MAST_PARAM_LIST") {
											_this.get_MasterLSJSON = websocketBody;
											_this.$session.set("get_MasterLSJSON", _this.get_MasterLSJSON);
											_this.$session.set("get_copy_MasterLSJSON", _this.get_MasterLSJSON);
										} else if (websocketBody.TYPE == "GET_DLMS_MN_MAST_PARAM_LIST") {
											_this.get_MasterMNJSON = websocketBody;
											_this.$session.set("get_MasterMNJSON", _this.get_MasterMNJSON);
											_this.$session.set("get_copy_MasterMNJSON", _this.get_MasterMNJSON);
										} else if (websocketBody.TYPE == "GET_DLMS_EVENT_MAST_PARAM_LIST") {
											_this.get_MasterEVENTJSON = websocketBody;
											_this.$session.set("get_MasterEVENTJSON", _this.get_MasterEVENTJSON);
											_this.$session.set("get_copy_MasterEVENTJSON", _this.get_MasterEVENTJSON);
										} else if (websocketBody.TYPE == "GET_DLMS_BILL_MAST_PARAM_LIST") {
											_this.get_MasterBILLJSON = websocketBody;
											_this.$session.set("get_MasterBILLJSON", _this.get_MasterBILLJSON);
											_this.$session.set("get_copy_MasterBILLJSON", _this.get_MasterBILLJSON);
										} else if (websocketBody.TYPE == "GET_DLMS_INST_PARAM_CONFIG") {
											_this.get_SelectedINSTJSON = websocketBody;
											_this.$session.set("get_SelectedINSTJSON", _this.get_SelectedINSTJSON);
											_this.$session.set("get_copy_SelectedINSTJSON", _this.get_SelectedINSTJSON);
										} else if (websocketBody.TYPE == "GET_DLMS_LS_PARAM_CONFIG") {
											_this.get_SelectedLSJSON = websocketBody;
											_this.$session.set("get_SelectedLSJSON", _this.get_SelectedLSJSON);
											_this.$session.set("get_copy_SelectedLSJSON", _this.get_SelectedLSJSON);
										} else if (websocketBody.TYPE == "GET_DLMS_MN_PARAM_CONFIG") {
											_this.get_SelectedMNJSON = websocketBody;
											_this.$session.set("get_SelectedMNJSON", _this.get_SelectedMNJSON);
											_this.$session.set("get_copy_SelectedMNJSON", _this.get_SelectedMNJSON);
										} else if (websocketBody.TYPE == "GET_DLMS_EVENT_PARAM_CONFIG") {
											_this.get_SelectedEVENTJSON = websocketBody;
											_this.$session.set("get_SelectedEVENTJSON", _this.get_SelectedEVENTJSON);
											_this.$session.set("get_copy_SelectedEVENTJSON", _this.get_SelectedEVENTJSON);
										} else if (websocketBody.TYPE == "GET_DLMS_BILL_PARAM_CONFIG") {
											_this.get_SelectedBILLJSON = websocketBody;
											_this.$session.set("get_SelectedBILLJSON", _this.get_SelectedBILLJSON);
											_this.$session.set("get_copy_SelectedBILLJSON", _this.get_SelectedBILLJSON);
										}
									}
								} catch (err) {
									RespData = '';
									console.log("Invalid data");
									console.log(err);
								}
							}


							_this.responseTXT = '';
							setTimeout(function () {
								return _this.$router.replace({ path: "/dcu/deviceconfig" });
							}, 3000);
						} catch (err) {}
					};
				} else {
					this.responseTXT = 'Username and Password Incorrect';
					return false;
				}
			} catch (error) {
				console.log('error :' + error);
			}
		},
		successMessage: function successMessage(msg) {
			this.$notice.success({
				title: "Notification",
				description: msg,
				duration: 3,
				onClose: function onClose() {}
			});
		},
		warningMessage: function warningMessage(msg) {
			this.$notice.warning({
				title: "Notification",
				description: msg,
				duration: 3,
				onClose: function onClose() {}
			});
		},
		infoMessage: function infoMessage(msg) {
			this.$notice.info({
				title: "Notification",
				description: msg,
				duration: 3,
				onClose: function onClose() {}
			});
		},
		errorMessage: function errorMessage(msg) {
			this.$notice.error({
				title: "Notification",
				description: msg,
				duration: 3,
				onClose: function onClose() {}
			});
		},
		loginAction1: function loginAction1() {
			var _this2 = this;

			try {
				console.log("correct -ENTER-data");
				this.isLoading = true;
				var randomval = Math.floor(1000 + Math.random() * 9000);
				this.$session.set("loginsession", "Login success!");
				this.$session.set("UserRole", this.userrole);

				console.log("correct --data");

				var websocketBody = { TYPE: 'vvvv' };

				console.log(websocketBody.TYPE);
				if (websocketBody.TYPE != "") {
					this.get_GenconfigJSON = {
						"TYPE": "GET_GEN_CONFIG",
						"SEQ_NUM": "7747",
						"CMD_TYPE": "GEN_CONFIG",
						"CMD_STATUS": "SUCCESS",
						"DATA": {
							"GenCfg": {
								"DcuID": "DCU_MAIN_001",
								"Location": "Bangalore",
								"EnableDbgLog": "Yes",
								"SerNum": "DCU_0001",
								"DbgLogLevel": "1",
								"DbgLogIp": "192.168.10.193"
							},
							"EthCfg": {
								"NumEthPorts": "1",
								"EthCfg": [{
									"CurrIp": "192.168.10.55",
									"NewIp": "192.168.10.55",
									"GW": "192.168.10.201",
									"NetMask": "255.255.255.255"
								}]
							},
							"SerPortCfg": { "NumSerPorts": "1",
								"PortCfg": [{ "BaudRate": "9600",
									"Databits": "8",
									"Stopbits": "1",
									"Parity": "None",
									"InfMode": "RS232_MODE"
								}] }, "AllowedMasterCfg": {
								"EnableAllowMaster": "Yes",
								"AllowedMasterList": [{ "Enable": "Yes", "Ip": "192.168.10.108" }, { "Enable": "Yes", "Ip": "192.168.10.109" }, { "Enable": "Yes", "Ip": "192.168.10.110" }, { "Enable": "Yes", "Ip": "192.168.10.111" }]
							},
							"NtpCfg": {
								"EnableNtp1": "Yes",
								"EnableNtp2": "Yes",
								"NtpPort1": "123",
								"NtpPort2": "123",
								"Interval": "30",
								"NtpIpAddr1": "192.168.10.92",
								"NtpIpAddr2": "192.168.10.75"
							},
							"ModemCfg": {
								"EnableModem": "Yes",
								"PingInt": "15",
								"NumPings": "10",
								"ConnType": "3G_TYPE",
								"EnablePing": "Yes",
								"IpAddr": "192.168.10.108",
								"AccessPtName": "airtelgprs.com",
								"PhoneNum": "*99***1#",
								"Password": "internet",
								"Username": "internet"
							},
							"VpnCfg": {
								"EnableVpn": "Yes",
								"Type": "IPSEC",
								"IPSecConfig": {
									"KeyLifeTime": "2",
									"AggrMode": "0",
									"NatTrav": "0",
									"Pfs": "1",
									"TunnelName": "RTU100021",
									"PreSharedKey": "softel123",
									"RightIp": "122.166.196.34",
									"RightId": "mguard@cmsgp.com",
									"LeftSubnet": "192.168.0.1",
									"LeftId": "RTU100021@cmsgp.com",
									"KeyingMode": "ikev1",
									"DhGrp": "2",
									"Encrpt": "5",
									"Authen": "10",
									"DhGrp2": "2",
									"Encrpt2": "5",
									"Authen2": "10"
								},
								"PPTPCfg": {
									"LocalUName": "vpnuser",
									"LocalPwd": "abc123",
									"RemUName": "pptpd",
									"RemPass": "pptpd",
									"Req_mmpe128": "1"
								}
							}
						}
					};
					this.$session.set("get_GenconfigJSON", this.get_GenconfigJSON);
					this.$session.set("get_copy_GenconfigJSON", this.get_GenconfigJSON);
				}
				if (websocketBody.TYPE != "GET_UPSTREAM_CONFIG") {
					this.get_UpstreamconfigJSON = {
						"TYPE": "GET_UPSTREAM_CONFIG",
						"SEQ_NUM": "9847",
						"CMD_TYPE": "UPSTREAM_CONFIG",
						"CMD_STATUS": "SUCCESS",
						"DATA": {
							"UpstreamDataCfg": {
								"FtpPushSupp": "Yes",
								"MQTTSupp": "Yes",
								"CMSEMSSupp": "Yes",
								"SMSSupp": "No",
								"IEC104Supp": "Yes",
								"ModTcpSupp": "Yes",
								"FileFormatSupp": "CSV"
							},
							"IEC104Cfg": {
								"StationAddr": "3",
								"CotSize": "2",
								"IoaSize": "3",
								"CycInt": "30",
								"PortNo": "2404",
								"MetStartIoa": "1000"
							},
							"SMSCfg": {
								"NoOfPhoneNum": "0",
								"Details": [{
									"Name": "User",
									"Num": "8080XXXXX"
								}]
							},
							"ModTcpCfg": {
								"RespToAllSlaveId": "Yes",
								"ModDevId": "1",
								"HoldRegStartAddr": "3000",
								"InputRegStartAddr": "4000",
								"ReadCoilStartAddr": "1000",
								"ReadDiscriteInputStartAddr": "0",
								"PortNo": "0"
							},
							"FtpServerCfg": {
								"PortNo": "21",
								"UploadPeriod": "15",
								"RemoteDir": "dlms_api_dir",
								"Password": "radhey$123",
								"UserName": "vijay",
								"ServerIp": "192.168.10.193",
								"DiffServerForLogs": "No",
								"LogPortNo": "21",
								"LogUploadPeriod": "15",
								"LogRemoteDir": "dlms_api_dir",
								"LogPassword": "radhey$123",
								"LogUserName": "vijay",
								"LogServerIp": "192.168.10.193"
							},
							"MQTTCfg": {
								"BrokerIp": "192.168.10.108",
								"Password": "softel",
								"UserName": "user",
								"PortNo": "1883",
								"CycDataTopic": "s",
								"CmdTopic": "s",
								"EnableDiagTopics": "No",
								"DiagTopic": "/cms/bangalore/diag",
								"EnableEventTopics": "No",
								"EventTopic": "/cms/bangalore/event",
								"PubHr": "0",
								"PubMint": "5",
								"CycPeriod": "0"
							},
							"CMSEMSCfg": {
								"BrokerIp": "15.206.196.77",
								"PortNo": "8010",
								"EnableEvent": "No",
								"EnableDiag": "No",
								"PubHr": "0",
								"PubMint": "5",
								"CycPeriod": "0"
							}
						}
					};
					this.$session.set("get_UpstreamconfigJSON", this.get_UpstreamconfigJSON);
					this.$session.set("get_copy_UpstreamconfigJSON", this.get_UpstreamconfigJSON);
				}
				if (websocketBody.TYPE != "GET_DLMS_CONFIG") {
					this.get_DlmsMeterconfigSON = {
						"TYPE": "GET_DLMS_CONFIG",
						"SEQ_NUM": "9386",
						"CMD_TYPE": "DLMS_CONFIG",
						"CMD_STATUS": "SUCCESS",
						"DATA": {
							"DLMSCfg": {
								"ReadPrevLsData": "Yes",
								"MeterType": "Serial",
								"FaultTolSupp": "No",
								"MaxMeters": "5",
								"EnableInstData": "Yes",
								"EnableBillingData": "Yes",
								"EnableEventData": "Yes",
								"EnableMidnightData": "Yes",
								"EnableLSData": "Yes",
								"MidnightPollPer": "1",
								"BillingPollPer": "2"
							},
							"DLMSEthMetCfg": {
								"NumMeters": "10",
								"EthMeters": [{
									"TO": "2", "RetCnt": "3", "Enable": "1", "Pwd": "0", "Ip": "254", "Loc": "DCU_MET_LOC_0", "Port": "0" }, {
									"TO": "2", "RetCnt": "3", "Enable": "1", "Pwd": "0", "Ip": "254", "Loc": "DCU_MET_LOC_1", "Port": "0" }, {
									"TO": "2", "RetCnt": "3", "Enable": "1", "Pwd": "0", "Ip": "254", "Loc": "DCU_MET_LOC_2", "Port": "0" }, {
									"TO": "2", "RetCnt": "3", "Enable": "1", "Pwd": "0", "Ip": "254", "Loc": "DCU_MET_LOC_3", "Port": "0" }, {
									"TO": "2", "RetCnt": "3", "Enable": "1", "Pwd": "0", "Ip": "254", "Loc": "DCU_MET_LOC_4", "Port": "0" }, {
									"TO": "2", "RetCnt": "3", "Enable": "1", "Pwd": "0", "Ip": "254", "Loc": "DCU_MET_LOC_5", "Port": "0" }, {
									"TO": "2", "RetCnt": "3", "Enable": "1", "Pwd": "0", "Ip": "254", "Loc": "DCU_MET_LOC_6", "Port": "0" }, {
									"TO": "2", "RetCnt": "3", "Enable": "1", "Pwd": "0", "Ip": "254", "Loc": "DCU_MET_LOC_7", "Port": "0" }, {
									"TO": "2", "RetCnt": "3", "Enable": "1", "Pwd": "0", "Ip": "254", "Loc": "DCU_MET_LOC_8", "Port": "0" }, {
									"TO": "2", "RetCnt": "3", "Enable": "1", "Pwd": "0", "Ip": "254", "Loc": "DCU_MET_LOC_9", "Port": "0" }]
							},
							"DLMSP0MetCfg": {
								"NumMeters": "5",
								"Meters": [{
									"TO": "2", "RetCnt": "3", "Enable": "1", "AddrType": "1", "Addr": "17", "Pwd": "lnt1", "Loc": "DCU_MET_LOC_1" }, {
									"TO": "2", "RetCnt": "3", "Enable": "0", "AddrType": "1", "Addr": "18", "Pwd": "lnt1", "Loc": "DCU_MET_LOC_2" }, {
									"TO": "2", "RetCnt": "3", "Enable": "0", "AddrType": "1", "Addr": "19", "Pwd": "lnt1", "Loc": "DCU_MET_LOC_3" }, {
									"TO": "2", "RetCnt": "3", "Enable": "0", "AddrType": "1", "Addr": "20", "Pwd": "lnt1", "Loc": "DCU_MET_LOC_4" }, {
									"TO": "2", "RetCnt": "3", "Enable": "0", "AddrType": "1", "Addr": "21", "Pwd": "lnt1", "Loc": "DCU_MET_LOC_5" }]
							}
						}
					};
					this.$session.set("get_DlmsMeterconfigSON", this.get_DlmsMeterconfigSON);
					this.$session.set("get_copy_DlmsMeterconfigSON", this.get_DlmsMeterconfigSON);
				}
				if (websocketBody.TYPE != "GET_DLMS_INST_MAST_PARAM_LIST") {
					this.get_MasterINSTJSON = {
						"TYPE": "GET_DLMS_INST_MAST_PARAM_LIST",
						"SEQ_NUM": "3395",
						"CMD_TYPE": "GET_DLMS_MASTER_PARAM_LIST",
						"CMD_STATUS": "SUCCESS",
						"DATA": {
							"InstParams": {
								"NumParams": "22",
								"ObisCodeList": [{
									"obis": "0.0.1.0.0.255",
									"def": "date_time"
								}, {
									"obis": "1.0.31.7.0.255",
									"def": "cur_ir"
								}, {
									"obis": "1.0.51.7.0.255",
									"def": "cur_iy"
								}, {
									"obis": "1.0.71.7.0.255",
									"def": "cur_ib"
								}, {
									"obis": "1.0.32.7.0.255",
									"def": "volt_r"
								}, {
									"obis": "1.0.52.7.0.255",
									"def": "volt_y"
								}, {
									"obis": "1.0.72.7.0.255",
									"def": "volt_b"
								}, {
									"obis": "1.0.33.7.0.255",
									"def": "pf_r"
								}, {
									"obis": "1.0.53.7.0.255",
									"def": "pf_y"
								}, {
									"obis": "1.0.73.7.0.255",
									"def": "pf_b"
								}, {
									"obis": "1.0.13.7.0.255",
									"def": " pf_avg"
								}, {
									"obis": "1.0.14.7.0.255",
									"def": "freq"
								}, {
									"obis": "1.0.9.7.0.255",
									"def": "kva"
								}, {
									"obis": "1.0.1.7.0.255",
									"def": "kw"
								}, {
									"obis": "1.0.3.7.0.255",
									"def": "kvar"
								}, {
									"obis": "0.0.0.1.2.255",
									"def": "bill_date"
								}, {
									"obis": "1.0.1.8.0.255",
									"def": "kwh"
								}, {
									"obis": "1.0.5.8.0.255",
									"def": "kvarh_lag"
								}, {
									"obis": "1.0.8.8.0.255",
									"def": "kvarh_lead"
								}, {
									"obis": "1.0.9.8.0.255",
									"def": "kvah"
								}, {
									"obis": "1.0.1.6.0.255",
									"def": "kwmd"
								}, {
									"obis": "1.0.9.6.0.255",
									"def": "kvamd"
								}]
							}
						}
					};
					this.$session.set("get_MasterINSTJSON", this.get_MasterINSTJSON);
					this.$session.set("get_copy_MasterINSTJSON", this.get_MasterINSTJSON);
				}
				if (websocketBody.TYPE != "GET_DLMS_LS_MAST_PARAM_LIST") {
					this.get_MasterLSJSON = {
						"TYPE": "GET_DLMS_LS_MAST_PARAM_LIST",
						"SEQ_NUM": "3395",
						"CMD_TYPE": "GET_DLMS_MASTER_PARAM_LIST",
						"CMD_STATUS": "SUCCESS",
						"DATA": {
							"LSParams": {
								"NumParams": "14",
								"ObisCodeList": [{
									"obis": "0.0.1.0.0.255",
									"def": "date_time"
								}, {
									"obis": "1.0.31.27.0.255",
									"def": " cur_ir"
								}, {
									"obis": "1.0.51.27.0.255",
									"def": "cur_iy"
								}, {
									"obis": "1.0.71.27.0.255",
									"def": "cur_ib"
								}, {
									"obis": "1.0.32.27.0.255",
									"def": " volt_r"
								}, {
									"obis": "1.0.52.27.0.255",
									"def": "volt_y"
								}, {
									"obis": "1.0.72.27.0.255",
									"def": "volt_b"
								}, {
									"obis": "1.0.14.27.0.255",
									"def": " freq"
								}, {
									"obis": "1.0.2.29.0.255",
									"def": "kwh_exp"
								}, {
									"obis": "1.0.1.29.0.255",
									"def": "kwh_imp"
								}, {
									"obis": "1.0.5.29.0.255",
									"def": " kvarh_lag"
								}, {
									"obis": "1.0.8.29.0.255",
									"def": "kvarh_lead"
								}, {
									"obis": "1.0.10.29.0.255",
									"def": "kvah_exp"
								}, {
									"obis": "1.0.9.29.0.255",
									"def": " kvah_imp"
								}]
							}
						}
					};
					this.$session.set("get_MasterLSJSON", this.get_MasterLSJSON);
					this.$session.set("get_copy_MasterLSJSON", this.get_MasterLSJSON);
				}
				if (websocketBody.TYPE != "GET_DLMS_MN_MAST_PARAM_LIST") {
					this.get_MasterMNJSON = {
						"TYPE": "GET_DLMS_MN_MAST_PARAM_LIST",
						"SEQ_NUM": "8805",
						"CMD_TYPE": "GET_DLMS_MASTER_PARAM_LIST",
						"CMD_STATUS": "SUCCESS",
						"DATA": {
							"MNParams": {
								"NumParams": "11",
								"ObisCodeList": [{
									"obis": "0.0.1.0.0.255",
									"def": "date_time"
								}, {
									"obis": "1.0.1.8.0.255",
									"def": " kwh_imp"
								}, {
									"obis": "1.0.2.8.0.255",
									"def": "kwh_exp"
								}, {
									"obis": "1.0.9.8.0.255",
									"def": "kvah_imp"
								}, {
									"obis": "1.0.10.8.0.255",
									"def": " kvah_exp"
								}, {
									"obis": "1.0.94.91.1.255",
									"def": "react_enhi"
								}, {
									"obis": "1.0.94.91.2.255",
									"def": "react_enlo"
								}, {
									"obis": "1.0.5.8.0.255",
									"def": " kvarh_q1"
								}, {
									"obis": "1.0.6.8.0.255",
									"def": " kvarh_q2"
								}, {
									"obis": "1.0.7.8.0.255",
									"def": " kvarh_q3"
								}, {
									"obis": "1.0.8.8.0.255",
									"def": " kvarh_q4"
								}]
							}
						}
					};
					this.$session.set("get_MasterMNJSON", this.get_MasterMNJSON);
					this.$session.set("get_copy_MasterMNJSON", this.get_MasterMNJSON);
				}
				if (websocketBody.TYPE != "GET_DLMS_EVENT_MAST_PARAM_LIST") {
					this.get_MasterEVENTJSON = {
						"TYPE": "GET_DLMS_EVENT_MAST_PARAM_LIST",
						"SEQ_NUM": "3043",
						"CMD_TYPE": "GET_DLMS_MASTER_PARAM_LIST",
						"CMD_STATUS": "SUCCESS",
						"DATA": {
							"EventParams": {
								"NumParams": "12",
								"ObisCodeList": [{
									"obis": "0.0.1.0.0.255",
									"def": "date_time"
								}, {
									"obis": "1.0.31.7.0.255",
									"def": " cur_ir"
								}, {
									"obis": "1.0.51.7.0.255",
									"def": "cur_iy"
								}, {
									"obis": "1.0.71.7.0.255",
									"def": "cur_ib"
								}, {
									"obis": "1.0.32.7.0.255",
									"def": " volt_r"
								}, {
									"obis": "1.0.52.7.0.255",
									"def": "volt_y"
								}, {
									"obis": "1.0.72.7.0.255",
									"def": "volt_b"
								}, {
									"obis": "1.0.33.7.0.255",
									"def": " pf_r"
								}, {
									"obis": "1.0.53.7.0.255",
									"def": "pf_y"
								}, {
									"obis": "1.0.73.7.0.255",
									"def": "pf_b"
								}, {
									"obis": "1.0.1.8.0.255",
									"def": " kwh"
								}, {
									"obis": "0.0.96.11.0.255",
									"def": "event_code"
								}]
							}
						}
					};
					this.$session.set("get_MasterEVENTJSON", this.get_MasterEVENTJSON);
					this.$session.set("get_copy_MasterEVENTJSON", this.get_MasterEVENTJSON);
				}
				if (websocketBody.TYPE != "GET_DLMS_BILL_MAST_PARAM_LIST") {
					this.get_MasterBILLJSON = {
						"TYPE": "GET_DLMS_BILL_MAST_PARAM_LIST",
						"SEQ_NUM": "3334",
						"CMD_TYPE": "GET_DLMS_MASTER_PARAM_LIST",
						"CMD_STATUS": "SUCCESS",
						"DATA": {
							"BillParams": {
								"NumParams": "40",
								"ObisCodeList": [{
									"obis": "0.0.1.0.0.255",
									"def": "date_time"
								}, {
									"obis": "1.0.13.0.0.255",
									"def": " sys_pf"
								}, {
									"obis": "1.0.1.8.0.255",
									"def": "kwh"
								}, {
									"obis": "1.0.1.8.1.255",
									"def": "kwh_tz1"
								}, {
									"obis": "1.0.1.8.2.255",
									"def": "kwh_tz2"
								}, {
									"obis": "1.0.1.8.3.255",
									"def": "kwh_tz3"
								}, {
									"obis": "1.0.1.8.4.255",
									"def": "kwh_tz4"
								}, {
									"obis": "1.0.1.8.5.255",
									"def": "kwh_tz5"
								}, {
									"obis": "1.0.1.8.6.255",
									"def": "kwh_tz6"
								}, {
									"obis": "1.0.1.8.7.255",
									"def": "kwh_tz7"
								}, {
									"obis": "1.0.1.8.8.255",
									"def": "kwh_tz8"
								}, {
									"obis": "1.0.5.8.0.255",
									"def": "kvarh_lag"
								}, {
									"obis": "1.0.8.8.0.255",
									"def": " kvarh_lead"
								}, {
									"obis": "1.0.9.8.0.255",
									"def": "kvah"
								}, {
									"obis": "1.0.9.8.1.255",
									"def": "kvah_tz1"
								}, {
									"obis": "1.0.9.8.2.255",
									"def": "kvah_tz2"
								}, {
									"obis": "1.0.9.8.3.255",
									"def": "kvah_tz3"
								}, {
									"obis": "1.0.9.8.4.255",
									"def": "kvah_tz4"
								}, {
									"obis": "1.0.9.8.5.255",
									"def": "kvah_tz5"
								}, {
									"obis": "1.0.9.8.6.255",
									"def": "kvah_tz6"
								}, {
									"obis": "1.0.9.8.7.255",
									"def": "kvah_tz7"
								}, {
									"obis": "1.0.9.8.8.255",
									"def": "kvah_tz8"
								}, {
									"obis": "1.0.1.6.0.255",
									"def": "kwmd"
								}, {
									"obis": "1.0.1.6.1.255",
									"def": "kwmd_tz1"
								}, {
									"obis": "1.0.1.6.2.255",
									"def": "kwmd_tz2"
								}, {
									"obis": "1.0.1.6.3.255",
									"def": "kwmd_tz3"
								}, {
									"obis": "1.0.1.6.4.255",
									"def": "kwmd_tz4"
								}, {
									"obis": "1.0.1.6.5.255",
									"def": "kwmd_tz5"
								}, {
									"obis": "1.0.1.6.6.255",
									"def": "kwmd_tz6"
								}, {
									"obis": "1.0.1.6.7.255",
									"def": "kwmd_tz7"
								}, {
									"obis": "1.0.1.6.8.255",
									"def": "kwmd_tz8"
								}, {
									"obis": "1.0.9.6.0.255",
									"def": "kvamd"
								}, {
									"obis": "1.0.9.6.1.255",
									"def": "kvamd_tz1"
								}, {
									"obis": "1.0.9.6.2.255",
									"def": "kvamd_tz2"
								}, {
									"obis": "1.0.9.6.3.255",
									"def": "kvamd_tz3"
								}, {
									"obis": "1.0.9.6.4.255",
									"def": "kvamd_tz4"
								}, {
									"obis": "1.0.9.6.5.255",
									"def": "kvamd_tz5"
								}, {
									"obis": "1.0.9.6.6.255",
									"def": "kvamd_tz6"
								}, {
									"obis": "1.0.9.6.7.255",
									"def": "kvamd_tz7"
								}, {
									"obis": "1.0.9.6.8.255",
									"def": "kvamd_tz8"
								}]
							}
						}
					};
					this.$session.set("get_MasterBILLJSON", this.get_MasterBILLJSON);
					this.$session.set("get_copy_MasterBILLJSON", this.get_MasterBILLJSON);
				}
				if (websocketBody.TYPE != "GET_DLMS_INST_PARAM_CONFIG") {
					this.get_SelectedINSTJSON = {
						"TYPE": "GET_DLMS_INST_PARAM_CONFIG",
						"SEQ_NUM": "2727",
						"CMD_TYPE": "DLMS_PARAM_CONFIG",
						"CMD_STATUS": "SUCCESS",
						"DATA": {
							"InstParams": {
								"NumParams": "18",
								"ObisCodeList": [{
									"obis": "0.0.1.0.0.255",
									"def": "date_time",
									"assign": "date_time"
								}, {
									"obis": "1.0.31.7.0.255",
									"def": " cur_ir",
									"assign": "CurR"
								}, {
									"obis": "1.0.51.7.0.255",
									"def": "cur_iy",
									"assign": "CurY"
								}, {
									"obis": "0.0.1.0.0.255",
									"def": "date_time",
									"assign": "date_time"
								}, {
									"obis": "1.0.31.7.0.255",
									"def": " cur_ir",
									"assign": "CurR"
								}, {
									"obis": "1.0.51.7.0.255",
									"def": "cur_iy",
									"assign": "CurY"
								}, {
									"obis": "0.0.1.0.0.255",
									"def": "date_time",
									"assign": "date_time"
								}, {
									"obis": "1.0.31.7.0.255",
									"def": " cur_ir",
									"assign": "CurR"
								}, {
									"obis": "1.0.51.7.0.255",
									"def": "cur_iy",
									"assign": "CurY"
								}, {
									"obis": "0.0.1.0.0.255",
									"def": "date_time",
									"assign": "date_time"
								}, {
									"obis": "1.0.31.7.0.255",
									"def": " cur_ir",
									"assign": "CurR"
								}, {
									"obis": "1.0.51.7.0.255",
									"def": "cur_iy",
									"assign": "CurY"
								}, {
									"obis": "0.0.1.0.0.255",
									"def": "date_time",
									"assign": "date_time"
								}, {
									"obis": "1.0.31.7.0.255",
									"def": " cur_ir",
									"assign": "CurR"
								}, {
									"obis": "1.0.51.7.0.255",
									"def": "cur_iy",
									"assign": "CurY"
								}, {
									"obis": "0.0.1.0.0.255",
									"def": "date_time",
									"assign": "date_time"
								}, {
									"obis": "1.0.31.7.0.255",
									"def": " cur_ir",
									"assign": "CurR"
								}, {
									"obis": "1.0.51.7.0.255",
									"def": "cur_iy",
									"assign": "CurY"
								}]
							}
						}
					};
					this.$session.set("get_SelectedINSTJSON", this.get_SelectedINSTJSON);
					this.$session.set("get_copy_SelectedINSTJSON", this.get_SelectedINSTJSON);
				}
				if (websocketBody.TYPE != "GET_DLMS_LS_PARAM_CONFIG") {
					this.get_SelectedLSJSON = {
						"TYPE": "GET_DLMS_LS_PARAM_CONFIG",
						"SEQ_NUM": "1859",
						"CMD_TYPE": "DLMS_PARAM_CONFIG",
						"CMD_STATUS": "SUCCESS",
						"DATA": {
							"LSParams": {
								"NumParams": "18",
								"ObisCodeList": [{
									"obis": "0.0.1.0.0.255",
									"def": "date_time",
									"assign": "date_time"
								}, {
									"obis": "1.0.31.7.0.255",
									"def": " cur_ir",
									"assign": "CurR"
								}, {
									"obis": "1.0.51.7.0.255",
									"def": "cur_iy",
									"assign": "CurY"
								}, {
									"obis": "0.0.1.0.0.255",
									"def": "date_time",
									"assign": "date_time"
								}, {
									"obis": "1.0.31.7.0.255",
									"def": " cur_ir",
									"assign": "CurR"
								}, {
									"obis": "1.0.51.7.0.255",
									"def": "cur_iy",
									"assign": "CurY"
								}, {
									"obis": "0.0.1.0.0.255",
									"def": "date_time",
									"assign": "date_time"
								}, {
									"obis": "1.0.31.7.0.255",
									"def": " cur_ir",
									"assign": "CurR"
								}, {
									"obis": "1.0.51.7.0.255",
									"def": "cur_iy",
									"assign": "CurY"
								}, {
									"obis": "0.0.1.0.0.255",
									"def": "date_time",
									"assign": "date_time"
								}, {
									"obis": "1.0.31.7.0.255",
									"def": " cur_ir",
									"assign": "CurR"
								}, {
									"obis": "1.0.51.7.0.255",
									"def": "cur_iy",
									"assign": "CurY"
								}, {
									"obis": "0.0.1.0.0.255",
									"def": "date_time",
									"assign": "date_time"
								}, {
									"obis": "1.0.31.7.0.255",
									"def": " cur_ir",
									"assign": "CurR"
								}, {
									"obis": "1.0.51.7.0.255",
									"def": "cur_iy",
									"assign": "CurY"
								}, {
									"obis": "0.0.1.0.0.255",
									"def": "date_time",
									"assign": "date_time"
								}, {
									"obis": "1.0.31.7.0.255",
									"def": " cur_ir",
									"assign": "CurR"
								}, {
									"obis": "1.0.51.7.0.255",
									"def": "cur_iy",
									"assign": "CurY"
								}]
							}
						}
					};
					this.$session.set("get_SelectedLSJSON", this.get_SelectedLSJSON);
					this.$session.set("get_copy_SelectedLSJSON", this.get_SelectedLSJSON);
				}
				if (websocketBody.TYPE != "GET_DLMS_MN_PARAM_CONFIG") {
					this.get_SelectedMNJSON = {
						"TYPE": "GET_DLMS_MN_PARAM_CONFIG",
						"SEQ_NUM": "3037",
						"CMD_TYPE": "DLMS_PARAM_CONFIG",
						"CMD_STATUS": "SUCCESS",
						"DATA": {
							"MNParams": {
								"NumParams": "18",
								"ObisCodeList": [{
									"obis": "0.0.1.0.0.255",
									"def": "date_time",
									"assign": "date_time"
								}, {
									"obis": "1.0.31.7.0.255",
									"def": " cur_ir",
									"assign": "CurR"
								}, {
									"obis": "1.0.51.7.0.255",
									"def": "cur_iy",
									"assign": "CurY"
								}, {
									"obis": "0.0.1.0.0.255",
									"def": "date_time",
									"assign": "date_time"
								}, {
									"obis": "1.0.31.7.0.255",
									"def": " cur_ir",
									"assign": "CurR"
								}, {
									"obis": "1.0.51.7.0.255",
									"def": "cur_iy",
									"assign": "CurY"
								}, {
									"obis": "0.0.1.0.0.255",
									"def": "date_time",
									"assign": "date_time"
								}, {
									"obis": "1.0.31.7.0.255",
									"def": " cur_ir",
									"assign": "CurR"
								}, {
									"obis": "1.0.51.7.0.255",
									"def": "cur_iy",
									"assign": "CurY"
								}, {
									"obis": "0.0.1.0.0.255",
									"def": "date_time",
									"assign": "date_time"
								}, {
									"obis": "1.0.31.7.0.255",
									"def": " cur_ir",
									"assign": "CurR"
								}, {
									"obis": "1.0.51.7.0.255",
									"def": "cur_iy",
									"assign": "CurY"
								}, {
									"obis": "0.0.1.0.0.255",
									"def": "date_time",
									"assign": "date_time"
								}, {
									"obis": "1.0.31.7.0.255",
									"def": " cur_ir",
									"assign": "CurR"
								}, {
									"obis": "1.0.51.7.0.255",
									"def": "cur_iy",
									"assign": "CurY"
								}, {
									"obis": "0.0.1.0.0.255",
									"def": "date_time",
									"assign": "date_time"
								}, {
									"obis": "1.0.31.7.0.255",
									"def": " cur_ir",
									"assign": "CurR"
								}, {
									"obis": "1.0.51.7.0.255",
									"def": "cur_iy",
									"assign": "CurY"
								}]
							}
						}
					};
					this.$session.set("get_SelectedMNJSON", this.get_SelectedMNJSON);
					this.$session.set("get_copy_SelectedMNJSON", this.get_SelectedMNJSON);
				}
				if (websocketBody.TYPE != "GET_DLMS_EVENT_PARAM_CONFIG") {
					this.get_SelectedEVENTJSON = {
						"TYPE": "GET_DLMS_EVENT_PARAM_CONFIG",
						"SEQ_NUM": "5440",
						"CMD_TYPE": "DLMS_PARAM_CONFIG",
						"CMD_STATUS": "SUCCESS",
						"DATA": {
							"EventParams": {
								"NumParams": "18",
								"ObisCodeList": [{
									"obis": "0.0.1.0.0.255",
									"def": "date_time",
									"assign": "date_time"
								}, {
									"obis": "1.0.31.7.0.255",
									"def": " cur_ir",
									"assign": "CurR"
								}, {
									"obis": "1.0.51.7.0.255",
									"def": "cur_iy",
									"assign": "CurY"
								}, {
									"obis": "0.0.1.0.0.255",
									"def": "date_time",
									"assign": "date_time"
								}, {
									"obis": "1.0.31.7.0.255",
									"def": " cur_ir",
									"assign": "CurR"
								}, {
									"obis": "1.0.51.7.0.255",
									"def": "cur_iy",
									"assign": "CurY"
								}, {
									"obis": "0.0.1.0.0.255",
									"def": "date_time",
									"assign": "date_time"
								}, {
									"obis": "1.0.31.7.0.255",
									"def": " cur_ir",
									"assign": "CurR"
								}, {
									"obis": "1.0.51.7.0.255",
									"def": "cur_iy",
									"assign": "CurY"
								}, {
									"obis": "0.0.1.0.0.255",
									"def": "date_time",
									"assign": "date_time"
								}, {
									"obis": "1.0.31.7.0.255",
									"def": " cur_ir",
									"assign": "CurR"
								}, {
									"obis": "1.0.51.7.0.255",
									"def": "cur_iy",
									"assign": "CurY"
								}, {
									"obis": "0.0.1.0.0.255",
									"def": "date_time",
									"assign": "date_time"
								}, {
									"obis": "1.0.31.7.0.255",
									"def": " cur_ir",
									"assign": "CurR"
								}, {
									"obis": "1.0.51.7.0.255",
									"def": "cur_iy",
									"assign": "CurY"
								}, {
									"obis": "0.0.1.0.0.255",
									"def": "date_time",
									"assign": "date_time"
								}, {
									"obis": "1.0.31.7.0.255",
									"def": " cur_ir",
									"assign": "CurR"
								}, {
									"obis": "1.0.51.7.0.255",
									"def": "cur_iy",
									"assign": "CurY"
								}]
							}
						}
					};
					this.$session.set("get_SelectedEVENTJSON", this.get_SelectedEVENTJSON);
					this.$session.set("get_copy_SelectedEVENTJSON", this.get_SelectedEVENTJSON);
				}
				if (websocketBody.TYPE != "GET_DLMS_BILL_PARAM_CONFIG") {
					this.get_SelectedBILLJSON = {
						"TYPE": "GET_DLMS_BILL_PARAM_CONFIG",
						"SEQ_NUM": "8774",
						"CMD_TYPE": "DLMS_PARAM_CONFIG",
						"CMD_STATUS": "SUCCESS",
						"DATA": {
							"BillParams": {
								"NumParams": "18",
								"ObisCodeList": [{
									"obis": "0.0.1.0.0.255",
									"def": "date_time",
									"assign": "date_time"
								}, {
									"obis": "1.0.31.7.0.255",
									"def": " cur_ir",
									"assign": "CurR"
								}, {
									"obis": "1.0.51.7.0.255",
									"def": "cur_iy",
									"assign": "CurY"
								}, {
									"obis": "0.0.1.0.0.255",
									"def": "date_time",
									"assign": "date_time"
								}, {
									"obis": "1.0.31.7.0.255",
									"def": " cur_ir",
									"assign": "CurR"
								}, {
									"obis": "1.0.51.7.0.255",
									"def": "cur_iy",
									"assign": "CurY"
								}, {
									"obis": "0.0.1.0.0.255",
									"def": "date_time",
									"assign": "date_time"
								}, {
									"obis": "1.0.31.7.0.255",
									"def": " cur_ir",
									"assign": "CurR"
								}, {
									"obis": "1.0.51.7.0.255",
									"def": "cur_iy",
									"assign": "CurY"
								}, {
									"obis": "0.0.1.0.0.255",
									"def": "date_time",
									"assign": "date_time"
								}, {
									"obis": "1.0.31.7.0.255",
									"def": " cur_ir",
									"assign": "CurR"
								}, {
									"obis": "1.0.51.7.0.255",
									"def": "cur_iy",
									"assign": "CurY"
								}, {
									"obis": "0.0.1.0.0.255",
									"def": "date_time",
									"assign": "date_time"
								}, {
									"obis": "1.0.31.7.0.255",
									"def": " cur_ir",
									"assign": "CurR"
								}, {
									"obis": "1.0.51.7.0.255",
									"def": "cur_iy",
									"assign": "CurY"
								}, {
									"obis": "0.0.1.0.0.255",
									"def": "date_time",
									"assign": "date_time"
								}, {
									"obis": "1.0.31.7.0.255",
									"def": " cur_ir",
									"assign": "CurR"
								}, {
									"obis": "1.0.51.7.0.255",
									"def": "cur_iy",
									"assign": "CurY"
								}]
							}
						}
					};
					this.$session.set("get_SelectedBILLJSON", this.get_SelectedBILLJSON);
					this.$session.set("get_copy_SelectedBILLJSON", this.get_SelectedBILLJSON);
				}
				this.responseTXT = '';
				setTimeout(function () {
					return _this2.$router.replace({ path: "/dcu/deviceconfig" });
				}, 1000);
			} catch (error) {
				console.log('error :' + error);
			}
		}
	}
});

/***/ }),
/* 31 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
Object.defineProperty(__webpack_exports__, "__esModule", { value: true });


/* harmony default export */ __webpack_exports__["default"] = ({
  name: 'DashFooter',
  data: function data() {
    return {
      year: new Date().getFullYear()
    };
  }
});

/***/ }),
/* 32 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
Object.defineProperty(__webpack_exports__, "__esModule", { value: true });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_babel_runtime_helpers_extends__ = __webpack_require__(6);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_babel_runtime_helpers_extends___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_helpers_extends__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_vuex__ = __webpack_require__(5);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__MessagesMenu__ = __webpack_require__(97);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__MessagesMenu___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_2__MessagesMenu__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__NotificationsMenu__ = __webpack_require__(99);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__NotificationsMenu___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_3__NotificationsMenu__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__TasksMenu__ = __webpack_require__(102);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__TasksMenu___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_4__TasksMenu__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_5__UserMenu__ = __webpack_require__(103);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_5__UserMenu___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_5__UserMenu__);









/* harmony default export */ __webpack_exports__["default"] = ({
  name: 'DashHeader',
  components: {
    MessagesMenu: __WEBPACK_IMPORTED_MODULE_2__MessagesMenu___default.a,
    NotificationsMenu: __WEBPACK_IMPORTED_MODULE_3__NotificationsMenu___default.a,
    TasksMenu: __WEBPACK_IMPORTED_MODULE_4__TasksMenu___default.a,
    UserMenu: __WEBPACK_IMPORTED_MODULE_5__UserMenu___default.a
  },
  props: ['user'],
  created: function created() {},
  destroyed: function destroyed() {},

  computed: __WEBPACK_IMPORTED_MODULE_0_babel_runtime_helpers_extends___default()({}, __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_1_vuex__["b" /* mapState */])(['userInfo']))
});

/***/ }),
/* 33 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
Object.defineProperty(__webpack_exports__, "__esModule", { value: true });


/* harmony default export */ __webpack_exports__["default"] = ({
  name: 'MessageItem',
  props: ['message']
});

/***/ }),
/* 34 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
Object.defineProperty(__webpack_exports__, "__esModule", { value: true });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_babel_runtime_helpers_extends__ = __webpack_require__(6);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_babel_runtime_helpers_extends___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_helpers_extends__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_vuex__ = __webpack_require__(5);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__MessageItem__ = __webpack_require__(96);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__MessageItem___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_2__MessageItem__);






/* harmony default export */ __webpack_exports__["default"] = ({
  name: 'MessagesMenu',
  components: {
    MessageItem: __WEBPACK_IMPORTED_MODULE_2__MessageItem___default.a
  },
  computed: __WEBPACK_IMPORTED_MODULE_0_babel_runtime_helpers_extends___default()({}, __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_1_vuex__["b" /* mapState */])(['userInfo']))
});

/***/ }),
/* 35 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
Object.defineProperty(__webpack_exports__, "__esModule", { value: true });


/* harmony default export */ __webpack_exports__["default"] = ({
  props: {
    notification: {
      type: Object,
      required: true
    }
  }
});

/***/ }),
/* 36 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
Object.defineProperty(__webpack_exports__, "__esModule", { value: true });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_babel_runtime_helpers_extends__ = __webpack_require__(6);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_babel_runtime_helpers_extends___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_helpers_extends__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_vuex__ = __webpack_require__(5);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__NotificationItem__ = __webpack_require__(98);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__NotificationItem___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_2__NotificationItem__);






/* harmony default export */ __webpack_exports__["default"] = ({
  name: 'NotificationsMenu',
  components: {
    NotificationItem: __WEBPACK_IMPORTED_MODULE_2__NotificationItem___default.a
  },
  data: function data() {
    return {
      tab: 'new'
    };
  },

  computed: __WEBPACK_IMPORTED_MODULE_0_babel_runtime_helpers_extends___default()({}, __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_1_vuex__["b" /* mapState */])(['userInfo']), {
    newNotifications: function newNotifications() {
      return this.userInfo.notifications.filter(function (n) {
        return !n.readAt;
      });
    },
    oldNotifications: function oldNotifications() {
      return this.userInfo.notifications.filter(function (n) {
        return n.readAt;
      });
    }
  }),
  methods: {
    markAllAsRead: function markAllAsRead() {
      event.stopPropagation();

      this.userInfo.notifications.filter(function (n) {
        return !n.readAt;
      }).forEach(function (notification) {
        notification.readAt = new Date().toUTCString;
      });
    },
    switchTab: function switchTab(event, tab) {
      event.stopPropagation();

      this.tab = tab;
    }
  }
});

/***/ }),
/* 37 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
Object.defineProperty(__webpack_exports__, "__esModule", { value: true });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__SidebarMenu__ = __webpack_require__(101);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__SidebarMenu___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_0__SidebarMenu__);



/* harmony default export */ __webpack_exports__["default"] = ({
  name: 'Sidebar',
  props: ['user'],
  components: { SidebarMenu: __WEBPACK_IMPORTED_MODULE_0__SidebarMenu___default.a },
  data: function data() {
    return {
      max: 0
    };
  },
  created: function created() {},

  methods: {}
});

/***/ }),
/* 38 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
Object.defineProperty(__webpack_exports__, "__esModule", { value: true });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify__ = __webpack_require__(3);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_vue__ = __webpack_require__(4);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2_crip_vue_notice__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2_crip_vue_notice___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_2_crip_vue_notice__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3_vue_element_loading__ = __webpack_require__(2);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3_vue_element_loading___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_3_vue_element_loading__);






/* harmony default export */ __webpack_exports__["default"] = ({
  name: 'SidebarMenu',
  components: {
    VueElementLoading: __WEBPACK_IMPORTED_MODULE_3_vue_element_loading___default.a,
    CripNotice: __WEBPACK_IMPORTED_MODULE_2_crip_vue_notice___default.a
  },
  data: function data() {
    return {
      sidebarLogsession: this.$session.get("loginsession"),
      sidebarDeviceConfigPageJSON: this.$session.get('get_GenconfigJSON'),
      sidebarUpstreamConfigPageJSON: this.$session.get('get_UpstreamconfigJSON'),
      sidebarMeterConfigPageJSON: this.$session.get('get_DlmsMeterconfigSON'),
      sidebarMasterINSTConfigPageJSON: this.$session.get('get_MasterINSTJSON'),
      sidebarMasterLSConfigPageJSON: this.$session.get('get_MasterLSJSON'),
      sidebarMasterMNConfigPageJSON: this.$session.get('get_MasterMNJSON'),
      sidebarMasterEVENTConfigPageJSON: this.$session.get('get_MasterEVENTJSON'),
      sidebarMasterBILLConfigPageJSON: this.$session.get('get_MasterBILLJSON'),
      sidebarSelINSTConfigPageJSON: this.$session.get('get_SelectedINSTJSON'),
      sidebarSelLSConfigPageJSON: this.$session.get('get_SelectedLSJSON'),
      sidebarSelMNConfigPageJSON: this.$session.get('get_SelectedMNJSON'),
      sidebarSelEVENTConfigPageJSON: this.$session.get('get_SelectedEVENTJSON'),
      sidebarSelBILLConfigPageJSON: this.$session.get('get_SelectedBILLJSON'),
      loading: '',
      blockdevice: false,
      msg: "",
      html: '',
      time: 60,
      isRunning: false,
      interval: null,
      checkwebsocket: false
    };
  },
  destroyed: function destroyed() {
    console.log("-------sidebar clear----------");
  },

  methods: {
    saveRestartFunction: function saveRestartFunction() {
      this.$router.replace({ path: '/dcu/saveandapply' });
    },
    restartunitFunction: function restartunitFunction() {
      var _this = this;

      this.ws = new WebSocket(this.webSocketUrl);
      var RespData = "";
      this.ws.onopen = function (e) {
        var commdObj1 = { "TYPE": "CMD_MESSAGE", "SEQ_NUM": Math.floor(1000 + Math.random() * 9000).toString(), "CMD_TYPE": "RESTART_UNIT" };
        _this.ws.send(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(commdObj1));
        _this.checkwebsocket = true;
      };
      this.ws.onmessage = function (e) {
        console.log("-------REstart recv----------" + __WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(e.data));
        var websocketBody = JSON.parse(e.data);
        if (websocketBody.TYPE == "RESTART_UNIT" && websocketBody.CMD_STATUS == "SUCCESS") {
          _this.blockdevice = true;
          _this.toggleTimer();
          setTimeout(_this.clearALLSession, 60000);
        } else if (websocketBody.TYPE == "RESTART_UNIT" && websocketBody.CMD_STATUS == "FAILURE") {
          alert("Restart command failure");
          return false;
        }
      };

      this.ws.onmessage = function (e) {
        if (e.data.length == 4096) {
          RespData = RespData + e.data;
        } else {
          RespData = RespData + e.data;
          try {
            var split_char = RespData.split('!');
            var count = split_char.length - 1;
            for (var idx = 0; idx < count; idx++) {
              var restartwebsocketBody = JSON.parse(split_char[idx]);
              RespData = '';
              if (restartwebsocketBody.TYPE == "RESTART_UNIT" && restartwebsocketBody.CMD_STATUS == "SUCCESS") {
                _this.blockdevice = true;
                _this.toggleTimer();
                setTimeout(_this.clearALLSession, 60000);
              } else if (restartwebsocketBody.TYPE == "RESTART_UNIT" && restartwebsocketBody.CMD_STATUS == "FAILURE") {
                alert("Restart command failure");
                return false;
              }
            }
          } catch (err) {
            RespData = '';
            console.log("Invalid data");
            console.log(err);
          }
        }
      };
    },
    toggleTimer: function toggleTimer() {
      if (this.isRunning) {
        clearInterval(this.interval);
      } else {
        this.interval = setInterval(this.incrementTime, 1000);
      }
      this.isRunning = !this.isRunning;
    },
    incrementTime: function incrementTime() {
      this.time = parseInt(this.time) - 1;
    },
    clearALLSession: function clearALLSession() {
      this.blockdevice = false;
      this.$session.clear("loginsession");
      this.$session.clear("UserRole");
      this.$session.clear("get_GenconfigJSON");
      this.$session.clear("get_UpstreamconfigJSON");
      this.$session.clear("get_DlmsMeterconfigSON");
      this.$session.clear("get_MasterINSTJSON");
      this.$session.clear("get_MasterLSJSON");
      this.$session.clear("get_MasterMNJSON");
      this.$session.clear("get_MasterEVENTJSON");
      this.$session.clear("get_MasterBILLJSON");
      this.$session.clear("get_SelectedINSTJSON");
      this.$session.clear("get_SelectedLSJSON");
      this.$session.clear("get_SelectedMNJSON");
      this.$session.clear("get_SelectedEVENTJSON");
      this.$session.clear("get_SelectedBILLJSON");

      this.$session.clear("get_copy_GenconfigJSON");
      this.$session.clear("get_copy_UpstreamconfigJSON");
      this.$session.clear("get_copy_DlmsMeterconfigSON");
      this.$session.clear("get_copy_MasterINSTJSON");
      this.$session.clear("get_copy_MasterLSJSON");
      this.$session.clear("get_copy_MasterMNJSON");
      this.$session.clear("get_copy_MasterEVENTJSON");
      this.$session.clear("get_copy_MasterBILLJSON");
      this.$session.clear("get_copy_SelectedINSTJSON");
      this.$session.clear("get_copy_SelectedLSJSON");
      this.$session.clear("get_copy_SelectedMNJSON");
      this.$session.clear("get_copy_SelectedEVENTJSON");
      this.$session.clear("get_copy_SelectedBILLJSON");
      if (this.checkwebsocket) {
        this.ws.close();
      }

      this.$router.replace({ path: '/' });
      clearInterval(this.interval);
    },
    ValidateIPaddress: function ValidateIPaddress(inputText) {
      console.log('inputText:', inputText);
      var ipformat = /^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/;
      if (inputText.match(ipformat)) {
        return true;
      } else {
        this.warningMessage("You have entered invalid IP address!");
        return false;
      }
    },
    successMessage: function successMessage(msg) {
      this.$notice.success({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    warningMessage: function warningMessage(msg) {
      this.$notice.warning({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    infoMessage: function infoMessage(msg) {
      this.$notice.info({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    errorMessage: function errorMessage(msg) {
      this.$notice.error({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    }
  }
});

/***/ }),
/* 39 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
Object.defineProperty(__webpack_exports__, "__esModule", { value: true });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_babel_runtime_helpers_extends__ = __webpack_require__(6);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_babel_runtime_helpers_extends___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_helpers_extends__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_vuex__ = __webpack_require__(5);





/* harmony default export */ __webpack_exports__["default"] = ({
  name: 'TasksMenu',
  computed: __WEBPACK_IMPORTED_MODULE_0_babel_runtime_helpers_extends___default()({}, __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_1_vuex__["b" /* mapState */])(['userInfo']))
});

/***/ }),
/* 40 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
Object.defineProperty(__webpack_exports__, "__esModule", { value: true });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_vue_element_loading__ = __webpack_require__(2);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_vue_element_loading___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_0_vue_element_loading__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_crip_vue_notice__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_crip_vue_notice___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_1_crip_vue_notice__);




/* harmony default export */ __webpack_exports__["default"] = ({
  name: 'UserMenu',
  props: ['user'],
  components: {
    CripNotice: __WEBPACK_IMPORTED_MODULE_1_crip_vue_notice___default.a,
    VueElementLoading: __WEBPACK_IMPORTED_MODULE_0_vue_element_loading___default.a
  },
  data: function data() {
    return {
      section: 'Login',
      loading: '',
      username: '',
      password: '',
      response: '',
      userrole: ''
    };
  },

  methods: {
    logoutAction: function logoutAction() {
      this.$router.replace({ name: 'Login' });
    }
  }

});

/***/ }),
/* 41 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
Object.defineProperty(__webpack_exports__, "__esModule", { value: true });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_crip_vue_notice__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_crip_vue_notice___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_0_crip_vue_notice__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_vue_element_loading__ = __webpack_require__(2);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_vue_element_loading___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_1_vue_element_loading__);




/* harmony default export */ __webpack_exports__["default"] = ({
  name: 'Changepass',
  components: {
    CripNotice: __WEBPACK_IMPORTED_MODULE_0_crip_vue_notice___default.a,
    VueElementLoading: __WEBPACK_IMPORTED_MODULE_1_vue_element_loading___default.a
  },
  data: function data() {
    return {
      isLoading: false,
      changeusernameTXT: '',
      changecurrpassTXT: '',
      changenewpassTXT: '',
      changeconfrimPassTXT: ''
    };
  },
  created: function created() {
    if (this.$session.get("loginsession") == "") {
      this.$router.replace({ path: '/' });
      return false;
    }
  },
  mounted: function mounted() {
    var _this = this;

    this.isLoading = true;
    var innerMinHeight = window.innerHeight - 122 + 'px';
    document.getElementById('changepassPage').style.minHeight = innerMinHeight;
    setTimeout(function () {
      return _this.isLoading = false;
    }, 200);
  },

  methods: {
    isNumber: function isNumber(evt) {
      evt = evt ? true : window.event;
      var charCode = evt.which ? evt.which : evt.keyCode;
      if (charCode > 31 && (charCode < 48 || charCode > 57) && charCode !== 46) {
        evt.preventDefault();
      } else {
        return true;
      }
    },
    successMessage: function successMessage(msg) {
      this.$notice.success({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    warningMessage: function warningMessage(msg) {
      this.$notice.warning({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    infoMessage: function infoMessage(msg) {
      this.$notice.info({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    errorMessage: function errorMessage(msg) {
      this.$notice.error({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    }
  }
});

/***/ }),
/* 42 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
Object.defineProperty(__webpack_exports__, "__esModule", { value: true });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify__ = __webpack_require__(3);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_vue__ = __webpack_require__(4);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2_crip_vue_notice__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2_crip_vue_notice___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_2_crip_vue_notice__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3_vue_element_loading__ = __webpack_require__(2);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3_vue_element_loading___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_3_vue_element_loading__);






/* harmony default export */ __webpack_exports__["default"] = ({
  name: 'DeviceConfig',
  components: {
    CripNotice: __WEBPACK_IMPORTED_MODULE_2_crip_vue_notice___default.a,
    VueElementLoading: __WEBPACK_IMPORTED_MODULE_3_vue_element_loading___default.a
  },
  data: function data() {
    return {
      deviceCONFIGPageJSON: this.$session.get("get_GenconfigJSON"),
      upstreamCONFIGjSON: this.$session.get("get_UpstreamconfigJSON"),
      dlmsmeterCONFIGPageJSON: this.$session.get("get_DlmsMeterconfigSON"),
      masterINSTCONFIGjSON: this.$session.get("get_MasterINSTJSON"),
      masterLSCONFIGjSON: this.$session.get("get_MasterLSJSON"),
      masterMNCONFIGjSON: this.$session.get("get_MasterMNJSON"),
      masterEVENTCONFIGjSON: this.$session.get("get_MasterEVENTJSON"),
      masterBILLCONFIGjSON: this.$session.get("get_MasterBILLJSON"),
      paramSelINSTCONFIGjSON: this.$session.get("get_SelectedINSTJSON"),
      paramSelLSCONFIGjSON: this.$session.get("get_SelectedLSJSON"),
      paramSelMNCONFIGjSON: this.$session.get("get_SelectedMNJSON"),
      paramSelEVENTCONFIGjSON: this.$session.get("get_SelectedEVENTJSON"),
      paramSelBILLCONFIGjSON: this.$session.get("get_SelectedBILLJSON"),
      isLoading: false,
      gendculocTXT: '',
      gendcuserialNumTXT: '',
      dbgEnablecheckbox: false,
      dbgloglvlTXT: 'choose Dbg Log Level',
      dbglogIPTXT: '',
      gendcuserialIDTXT: '',
      lancurrIpTXT: '',
      lannewIpTXT: '',
      lansubnetmaskIpTXT: '',
      langatewayIpTXT: '',
      lancurrIp2TXT: '',
      lannewIp2TXT: '',
      lansubnetmaskIp2TXT: '',
      langatewayIp2TXT: '',
      ethnetcount: '2',
      iec104Enablechekbox: false,
      ftpEnablechekbox: false,
      ftpIpaddTXT: '',
      ftpprtnoTXT: '',
      ftpusernameTXT: '',
      ftppasswordTXT: '',
      ftpdirTXT: '',
      ftptimeoutTXT: '15',
      enethernet1Checkbox: true,
      enethernet2Checkbox: false,
      lancurrentipaddressTXT: '',
      genLANNewIPTXT: '',
      gensubnetMaskIPTXT: '',
      genGatewayaddressIPTXT: '',
      lancurrentipaddressTXT2: '',
      genLANNewIPTXT2: '',
      gensubnetMaskIPTXT2: '',
      genGatewayaddressIPTXT2: '',
      gendebugipcheckbox: false,
      gendebugIPTXT: '',
      modemEnablechekbox: false,
      modemUsernameTXT: '',
      modemPasswordTXT: '',
      modemPhoneTXT: '',
      modemAPNTXT: '',
      pingEnablenethealthchekbox: false,
      modemPingIPTXT: '',
      modemPingIntervalTXT: 'choose ping interval',
      modemNumofPingTXT: 'choose no of ping',
      smbEnableSMShekbox: false,
      smsnumberDetailsArray: [],
      mbEnablenethealthchekbox: false,
      mbPingIPTXT: '',
      mbPingIntervalTXT: '',
      mbNumofPingTXT: '',
      ntpStatedwnTXT1chekbox: false,
      ntpserverIPAddressTXT1: '',
      ntpserverPortTXT1: '',
      ntpStatedwnTXT2chekbox: false,
      ntpserverIPAddressTXT2: '',
      ntpserverPortTXT2: '',
      ntpserverIntervalTXT: 'choose ntp interval',
      ntpservercommnicationdwnTXT: 'Choose Protocol',
      iecStationTXT: '',
      startIOAaddTXT: '',
      iecCodsizedwnTXT: 'Choose COT Size',
      iecCylicTXT: '',
      iecIOAsizedwnTXT: 'Choose IOA Size',
      iecTSTAdwnTXT: 'Choose TSTA',
      iecTSTAstartAddresTXT: '',
      iecTimeout1TXT: '',
      iecTimeout2TXT: '',
      iecTimeout3TXT: '',
      iecTimeoutportTXT: '',
      vpnEnablechekbox: false,
      vpntypeTXT: 'IPSEC',
      vpnTunnalNameTXT: '',
      vpnPreSharedKeyTXT: '',
      vpnKeyLifeTimeTXT: '',
      vpnRightIpTXT: '',
      vpnRightSubnetTXT: '',
      vpnRightIdTXT: '',
      vpnLeftSubnetTXT: '',
      vpnLeftIdTXT: '',
      vpnPfsTXT: '',
      vpnAggrModeTXT: '',
      VpnKeyingModeTXT: '',
      vpnNatTravTXT: '',
      vpnDhGrpTXT: '',
      vpnEncrptTXT: '',
      vpnAuthenTXT: '',
      vpnDhGrp2TXT: '',
      vpnEncrpt2TXT: '',
      vpnAuthen2TXT: '',
      vpnConnNameTXT: '',
      vpnLocalUNameTXT: '',
      vpnLocalPwdTXT: '',
      vpnRemIpTXT: '',
      vpnRemUNameTXT: '',
      vpnReq_mmpe128TXT: ''
    };
  },
  mounted: function mounted() {
    var _this = this;

    this.isLoading = true;
    var innerMinHeight = window.innerHeight - 130 + 'px';
    document.getElementById('generalsettingPagePANE').style.minHeight = innerMinHeight;
    setTimeout(function () {
      return _this.isLoading = false;
    }, 500);
  },
  created: function created() {
    if (this.$session.get("loginsession") == "") {
      this.$router.replace({ path: '/' });
      return false;
    }
    this.deviceConfigPageLoad();
  },

  updated: function updated() {
    this.saveDeviceConfig();
  },
  beforeDestroy: function beforeDestroy() {
    this.deviceConfigPageValidation();
  },

  methods: {
    deviceConfigPageLoad: function deviceConfigPageLoad() {
      if (this.deviceCONFIGPageJSON.hasOwnProperty("DATA")) {
        if (this.deviceCONFIGPageJSON.DATA.hasOwnProperty("GenCfg")) {
          this.gendcuserialIDTXT = this.deviceCONFIGPageJSON.DATA.GenCfg.hasOwnProperty("DcuID") ? this.deviceCONFIGPageJSON.DATA.GenCfg.DcuID : "";
          this.gendculocTXT = this.deviceCONFIGPageJSON.DATA.GenCfg.hasOwnProperty("Location") ? this.deviceCONFIGPageJSON.DATA.GenCfg.Location : "";
          this.gendcuserialNumTXT = this.deviceCONFIGPageJSON.DATA.GenCfg.hasOwnProperty("SerNum") ? this.deviceCONFIGPageJSON.DATA.GenCfg.SerNum : "";
          this.dbgEnablecheckbox = this.deviceCONFIGPageJSON.DATA.GenCfg.hasOwnProperty("EnableDbgLog") ? this.deviceCONFIGPageJSON.DATA.GenCfg.EnableDbgLog == 'No' ? false : true : false;
          this.dbgloglvlTXT = this.deviceCONFIGPageJSON.DATA.GenCfg.hasOwnProperty("DbgLogLevel") ? this.deviceCONFIGPageJSON.DATA.GenCfg.DbgLogLevel : "choose Dbg Log Level";
          this.dbglogIPTXT = this.deviceCONFIGPageJSON.DATA.GenCfg.hasOwnProperty("DbgLogIp") ? this.deviceCONFIGPageJSON.DATA.GenCfg.DbgLogIp : "";
        }
        if (this.deviceCONFIGPageJSON.DATA.hasOwnProperty("EthCfg")) {
          this.ethnetcount = this.deviceCONFIGPageJSON.DATA.EthCfg.hasOwnProperty("NumEthPorts") ? this.deviceCONFIGPageJSON.DATA.EthCfg.NumEthPorts : "";
          this.lancurrIpTXT = this.deviceCONFIGPageJSON.DATA.EthCfg.EthCfg[0].CurrIp == undefined ? "" : this.deviceCONFIGPageJSON.DATA.EthCfg.EthCfg[0].CurrIp;
          this.lannewIpTXT = this.deviceCONFIGPageJSON.DATA.EthCfg.EthCfg[0].NewIp == undefined ? "" : this.deviceCONFIGPageJSON.DATA.EthCfg.EthCfg[0].NewIp;
          this.lansubnetmaskIpTXT = this.deviceCONFIGPageJSON.DATA.EthCfg.EthCfg[0].NetMask == undefined ? "" : this.deviceCONFIGPageJSON.DATA.EthCfg.EthCfg[0].NetMask;
          this.langatewayIpTXT = this.deviceCONFIGPageJSON.DATA.EthCfg.EthCfg[0].GW == undefined ? "" : this.deviceCONFIGPageJSON.DATA.EthCfg.EthCfg[0].GW;
          if (this.deviceCONFIGPageJSON.DATA.EthCfg.NumEthPorts == "2") {
            this.lancurrIp2TXT = this.deviceCONFIGPageJSON.DATA.EthCfg.EthCfg[1].CurrIp == undefined ? "" : this.deviceCONFIGPageJSON.DATA.EthCfg.EthCfg[1].CurrIp;
            this.lannewIp2TXT = this.deviceCONFIGPageJSON.DATA.EthCfg.EthCfg[1].NewIp == undefined ? "" : this.deviceCONFIGPageJSON.DATA.EthCfg.EthCfg[1].NewIp;
            this.lansubnetmaskIp2TXT = this.deviceCONFIGPageJSON.DATA.EthCfg.EthCfg[1].NetMask == undefined ? "" : this.deviceCONFIGPageJSON.DATA.EthCfg.EthCfg[1].NetMask;
            this.langatewayIp2TXT = this.deviceCONFIGPageJSON.DATA.EthCfg.EthCfg[1].GW == undefined ? "" : this.deviceCONFIGPageJSON.DATA.EthCfg.EthCfg[1].GW;
          }
        }

        if (this.deviceCONFIGPageJSON.DATA.hasOwnProperty("ModemCfg")) {
          this.modemEnablechekbox = this.deviceCONFIGPageJSON.DATA.ModemCfg.EnableModem == undefined ? false : this.deviceCONFIGPageJSON.DATA.ModemCfg.EnableModem == 'No' ? false : true;
          this.modemUsernameTXT = this.deviceCONFIGPageJSON.DATA.ModemCfg.Username == undefined ? "" : this.deviceCONFIGPageJSON.DATA.ModemCfg.Username;
          this.modemPasswordTXT = this.deviceCONFIGPageJSON.DATA.ModemCfg.Password == undefined ? "" : this.deviceCONFIGPageJSON.DATA.ModemCfg.Password;
          this.modemPhoneTXT = this.deviceCONFIGPageJSON.DATA.ModemCfg.PhoneNum == undefined ? "" : this.deviceCONFIGPageJSON.DATA.ModemCfg.PhoneNum;
          this.modemAPNTXT = this.deviceCONFIGPageJSON.DATA.ModemCfg.AccessPtName == undefined ? "" : this.deviceCONFIGPageJSON.DATA.ModemCfg.AccessPtName;
          this.pingEnablenethealthchekbox = this.deviceCONFIGPageJSON.DATA.ModemCfg.EnablePing == undefined ? false : this.deviceCONFIGPageJSON.DATA.ModemCfg.EnablePing == 'No' ? false : true;
          this.modemPingIPTXT = this.deviceCONFIGPageJSON.DATA.ModemCfg.IpAddr == undefined ? "" : this.deviceCONFIGPageJSON.DATA.ModemCfg.IpAddr;
          this.modemPingIntervalTXT = this.deviceCONFIGPageJSON.DATA.ModemCfg.PingInt == undefined ? "" : this.deviceCONFIGPageJSON.DATA.ModemCfg.PingInt;
          this.modemNumofPingTXT = this.deviceCONFIGPageJSON.DATA.ModemCfg.NumPings == undefined ? "" : this.deviceCONFIGPageJSON.DATA.ModemCfg.NumPings;
        }

        if (this.deviceCONFIGPageJSON.DATA.hasOwnProperty("VpnCfg")) {
          this.vpnEnablechekbox = this.deviceCONFIGPageJSON.DATA.VpnCfg.EnableVpn == undefined ? false : this.deviceCONFIGPageJSON.DATA.VpnCfg.EnableVpn == 'No' ? false : true;
          this.vpntypeTXT = this.deviceCONFIGPageJSON.DATA.VpnCfg.Type == undefined ? "" : this.deviceCONFIGPageJSON.DATA.VpnCfg.Type;
          if (this.deviceCONFIGPageJSON.DATA.VpnCfg.Type == "IPSEC") {
            this.vpnTunnalNameTXT = this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.TunnelName == undefined ? "" : this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.TunnelName;
            this.vpnPreSharedKeyTXT = this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.PreSharedKey == undefined ? "" : this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.PreSharedKey;
            this.vpnKeyLifeTimeTXT = this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.KeyLifeTime == undefined ? "" : this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.KeyLifeTime;
            this.vpnRightIpTXT = this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.RightIp == undefined ? "" : this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.RightIp;
            this.vpnRightSubnetTXT = this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.RightSubnet == undefined ? "" : this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.RightSubnet;
            this.vpnRightIdTXT = this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.RightId == undefined ? "" : this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.RightId;
            this.vpnLeftSubnetTXT = this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.LeftSubnet == undefined ? "" : this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.LeftSubnet;
            this.vpnLeftIdTXT = this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.LeftId == undefined ? "" : this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.LeftId;
            this.vpnPfsTXT = this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.Pfs == undefined ? "" : this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.Pfs;
            this.vpnAggrModeTXT = this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.AggrMode == undefined ? "" : this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.AggrMode;
            this.VpnKeyingModeTXT = this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.KeyingMode == undefined ? "" : this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.KeyingMode;
            this.vpnNatTravTXT = this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.NatTrav == undefined ? "" : this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.NatTrav;
            this.vpnDhGrpTXT = this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.DhGrp == undefined ? "" : this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.DhGrp;
            this.vpnEncrptTXT = this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.Encrpt == undefined ? "" : this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.Encrpt;
            this.vpnAuthenTXT = this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.Authen == undefined ? "" : this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.Authen;
            this.vpnDhGrp2TXT = this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.DhGrp2 == undefined ? "" : this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.DhGrp2;
            this.vpnEncrpt2TXT = this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.Encrpt2 == undefined ? "" : this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.Encrpt2;
            this.vpnAuthen2TXT = this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.Authen2 == undefined ? "" : this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.Authen2;
          } else {
            this.vpnConnNameTXT = this.deviceCONFIGPageJSON.DATA.VpnCfg.PPTPCfg.ConnName == undefined ? "" : this.deviceCONFIGPageJSON.DATA.VpnCfg.PPTPCfg.ConnName;
            this.vpnLocalUNameTXT = this.deviceCONFIGPageJSON.DATA.VpnCfg.PPTPCfg.LocalUName == undefined ? "" : this.deviceCONFIGPageJSON.DATA.VpnCfg.PPTPCfg.LocalUName;
            this.vpnLocalPwdTXT = this.deviceCONFIGPageJSON.DATA.VpnCfg.PPTPCfg.LocalPwd == undefined ? "" : this.deviceCONFIGPageJSON.DATA.VpnCfg.PPTPCfg.LocalPwd;
            this.vpnRemIpTXT = this.deviceCONFIGPageJSON.DATA.VpnCfg.PPTPCfg.RemIp == undefined ? "" : this.deviceCONFIGPageJSON.DATA.VpnCfg.PPTPCfg.RemIp;
            this.vpnRemUNameTXT = this.deviceCONFIGPageJSON.DATA.VpnCfg.PPTPCfg.RemUName == undefined ? "" : this.deviceCONFIGPageJSON.DATA.VpnCfg.PPTPCfg.RemUName;
            this.vpnReq_mmpe128TXT = this.deviceCONFIGPageJSON.DATA.VpnCfg.PPTPCfg.Req_mmpe128 == undefined ? "" : this.deviceCONFIGPageJSON.DATA.VpnCfg.PPTPCfg.Req_mmpe128;
          }
        }

        if (this.deviceCONFIGPageJSON.DATA.hasOwnProperty("NtpCfg")) {
          this.ntpStatedwnTXT1chekbox = this.deviceCONFIGPageJSON.DATA.NtpCfg.EnableNtp1 == undefined ? "" : this.deviceCONFIGPageJSON.DATA.NtpCfg.EnableNtp1;
          this.ntpserverIPAddressTXT1 = this.deviceCONFIGPageJSON.DATA.NtpCfg.NtpIpAddr1 == undefined ? "" : this.deviceCONFIGPageJSON.DATA.NtpCfg.NtpIpAddr1;
          this.ntpserverPortTXT1 = this.deviceCONFIGPageJSON.DATA.NtpCfg.NtpPort1 == undefined ? "" : this.deviceCONFIGPageJSON.DATA.NtpCfg.NtpPort1;
          this.ntpStatedwnTXT2chekbox = this.deviceCONFIGPageJSON.DATA.NtpCfg.EnableNtp2 == undefined ? "" : this.deviceCONFIGPageJSON.DATA.NtpCfg.EnableNtp2;
          this.ntpserverIPAddressTXT2 = this.deviceCONFIGPageJSON.DATA.NtpCfg.NtpIpAddr2 == undefined ? "" : this.deviceCONFIGPageJSON.DATA.NtpCfg.NtpIpAddr2;
          this.ntpserverPortTXT2 = this.deviceCONFIGPageJSON.DATA.NtpCfg.NtpPort2 == undefined ? "" : this.deviceCONFIGPageJSON.DATA.NtpCfg.NtpPort2;
          this.ntpserverIntervalTXT = this.deviceCONFIGPageJSON.DATA.NtpCfg.Interval == undefined ? "" : this.deviceCONFIGPageJSON.DATA.NtpCfg.Interval;
        }
      }
      if (this.upstreamCONFIGjSON.hasOwnProperty("DATA") && this.upstreamCONFIGjSON.DATA.hasOwnProperty("UpstreamDataCfg")) {
        this.smbEnableSMShekbox = this.upstreamCONFIGjSON.DATA.UpstreamDataCfg.SMSSupp == undefined ? false : this.upstreamCONFIGjSON.DATA.UpstreamDataCfg.SMSSupp == 'No' ? false : true;
        this.smsnumberDetailsArray = this.upstreamCONFIGjSON.DATA.SMSCfg.Details;
      }
    },
    jsonEqual: function jsonEqual(a, b) {
      return __WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(a) === __WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(b);
    },
    saveDeviceConfig: function saveDeviceConfig() {
      this.deviceCONFIGPageJSON.DATA['GenCfg']['DcuID'] = this.gendcuserialIDTXT;
      this.deviceCONFIGPageJSON.DATA['GenCfg']['Location'] = this.gendculocTXT;
      this.deviceCONFIGPageJSON.DATA['GenCfg']['SerNum'] = this.gendcuserialNumTXT;
      this.deviceCONFIGPageJSON.DATA['GenCfg']['EnableDbgLog'] = this.dbgEnablecheckbox == true ? "Yes" : "No";
      this.deviceCONFIGPageJSON.DATA['GenCfg']['DbgLogLevel'] = this.dbgloglvlTXT;
      this.deviceCONFIGPageJSON.DATA['GenCfg']['DbgLogIp'] = this.dbglogIPTXT;

      this.deviceCONFIGPageJSON.DATA['EthCfg']['NumEthPorts'] = this.ethnetcount;
      this.deviceCONFIGPageJSON.DATA['EthCfg']['EthCfg'][0].CurrIp = this.lancurrIpTXT;
      this.deviceCONFIGPageJSON.DATA['EthCfg']['EthCfg'][0].NewIp = this.lannewIpTXT;
      this.deviceCONFIGPageJSON.DATA['EthCfg']['EthCfg'][0].NetMask = this.lansubnetmaskIpTXT;
      this.deviceCONFIGPageJSON.DATA['EthCfg']['EthCfg'][0].GW = this.langatewayIpTXT;

      if (this.deviceCONFIGPageJSON.DATA.EthCfg.NumEthPorts == "2") {
        this.deviceCONFIGPageJSON.DATA['EthCfg']['EthCfg'][1].CurrIp = this.lancurrIp2TXT;
        this.deviceCONFIGPageJSON.DATA['EthCfg']['EthCfg'][1].NewIp = this.lannewIp2TXT;
        this.deviceCONFIGPageJSON.DATA['EthCfg']['EthCfg'][1].NetMask = this.lansubnetmaskIp2TXT;
        this.deviceCONFIGPageJSON.DATA['EthCfg']['EthCfg'][1].GW = this.langatewayIp2TXT;
      }

      this.deviceCONFIGPageJSON.DATA.ModemCfg.EnableModem = this.modemEnablechekbox == true ? "Yes" : "No";
      this.deviceCONFIGPageJSON.DATA.ModemCfg.Username = this.modemUsernameTXT;
      this.deviceCONFIGPageJSON.DATA.ModemCfg.Password = this.modemPasswordTXT;
      this.deviceCONFIGPageJSON.DATA.ModemCfg.PhoneNum = this.modemPhoneTXT;
      this.deviceCONFIGPageJSON.DATA.ModemCfg.AccessPtName = this.modemAPNTXT;
      this.deviceCONFIGPageJSON.DATA.ModemCfg.EnablePing = this.pingEnablenethealthchekbox == true ? "Yes" : "No";
      this.deviceCONFIGPageJSON.DATA.ModemCfg.IpAddr = this.modemPingIPTXT;
      this.deviceCONFIGPageJSON.DATA.ModemCfg.PingInt = this.modemPingIntervalTXT;
      this.deviceCONFIGPageJSON.DATA.ModemCfg.NumPings = this.modemNumofPingTXT;

      this.upstreamCONFIGjSON.DATA.UpstreamDataCfg.SMSSupp = this.smbEnableSMShekbox == true ? "Yes" : "No";
      this.upstreamCONFIGjSON.DATA.SMSCfg.NoOfPhoneNum = this.smsnumberDetailsArray.length.toString();
      this.upstreamCONFIGjSON.DATA.SMSCfg.Details = this.smsnumberDetailsArray;

      for (var mm = 0; mm < this.upstreamCONFIGjSON.DATA.SMSCfg.Details.length; mm++) {
        this.upstreamCONFIGjSON.DATA.SMSCfg.Details[mm].Name = document.getElementById("smsNAMETXT" + (mm + 1)).value;
        this.upstreamCONFIGjSON.DATA.SMSCfg.Details[mm].Num = document.getElementById("smsphNUMTXT" + (mm + 1)).value;
      }

      this.deviceCONFIGPageJSON.DATA.VpnCfg.EnableVpn = this.vpnEnablechekbox == true ? "Yes" : "No";
      this.deviceCONFIGPageJSON.DATA.VpnCfg.Type = this.vpntypeTXT;
      if (this.deviceCONFIGPageJSON.DATA.VpnCfg.Type == "IPSEC") {
        this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.TunnelName = this.vpnTunnalNameTXT;
        this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.PreSharedKey = this.vpnPreSharedKeyTXT;
        this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.KeyLifeTime = this.vpnKeyLifeTimeTXT;
        this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.RightIp = this.vpnRightIpTXT;
        this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.RightSubnet = this.vpnRightSubnetTXT;
        this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.RightId = this.vpnRightIdTXT;
        this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.LeftSubnet = this.vpnLeftSubnetTXT;
        this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.LeftId = this.vpnLeftIdTXT;
        this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.Pfs = this.vpnPfsTXT;
        this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.AggrMode = this.vpnAggrModeTXT;
        this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.KeyingMode = this.VpnKeyingModeTXT;
        this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.NatTrav = this.vpnNatTravTXT;
        this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.DhGrp = this.vpnDhGrpTXT;
        this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.Encrpt = this.vpnEncrptTXT;
        this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.Authen = this.vpnAuthenTXT;
        this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.DhGrp2 = this.vpnDhGrp2TXT;
        this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.Encrpt2 = this.vpnEncrpt2TXT;
        this.deviceCONFIGPageJSON.DATA.VpnCfg.IPSecConfig.Authen2 = this.vpnAuthen2TXT;
      } else {
        this.deviceCONFIGPageJSON.DATA.VpnCfg.PPTPCfg.ConnName = this.vpnConnNameTXT;
        this.deviceCONFIGPageJSON.DATA.VpnCfg.PPTPCfg.LocalUName = this.vpnLocalUNameTXT;
        this.deviceCONFIGPageJSON.DATA.VpnCfg.PPTPCfg.LocalPwd = this.vpnLocalPwdTXT;
        this.deviceCONFIGPageJSON.DATA.VpnCfg.PPTPCfg.RemIp = this.vpnRemIpTXT;
        this.deviceCONFIGPageJSON.DATA.VpnCfg.PPTPCfg.RemUName = this.vpnRemUNameTXT;
        this.deviceCONFIGPageJSON.DATA.VpnCfg.PPTPCfg.Req_mmpe128 = this.vpnReq_mmpe128TXT;
      }

      this.deviceCONFIGPageJSON.DATA.NtpCfg.EnableNtp1 = this.ntpStatedwnTXT1chekbox;
      this.deviceCONFIGPageJSON.DATA.NtpCfg.NtpIpAddr1 = this.ntpserverIPAddressTXT1;
      this.deviceCONFIGPageJSON.DATA.NtpCfg.NtpPort1 = this.ntpserverPortTXT1;
      this.deviceCONFIGPageJSON.DATA.NtpCfg.EnableNtp2 = this.ntpStatedwnTXT2chekbox;
      this.deviceCONFIGPageJSON.DATA.NtpCfg.NtpIpAddr2 = this.ntpserverIPAddressTXT2;
      this.deviceCONFIGPageJSON.DATA.NtpCfg.NtpPort2 = this.ntpserverPortTXT2;
      this.deviceCONFIGPageJSON.DATA.NtpCfg.Interval = this.ntpserverIntervalTXT;

      this.$session.set('get_GenconfigJSON', this.deviceCONFIGPageJSON);
      this.$session.set('get_UpstreamconfigJSON', this.upstreamCONFIGjSON);
    },
    deviceConfigPageValidation: function deviceConfigPageValidation() {
      if (this.gendcuserialIDTXT === "" || this.gendcuserialIDTXT === null) {
        this.warningMessage("Please enter a dcu id");
        this.$router.replace({ path: '/dcu/deviceconfig' });
        return false;
      }

      if (this.gendculocTXT === "" || this.gendculocTXT == null) {
        this.warningMessage("Please enter a dcu location");
        this.$router.replace({ path: '/dcu/deviceconfig' });
        return false;
      }
      if (this.gendcuserialNumTXT === "" || this.gendcuserialNumTXT == null) {
        this.warningMessage("Please enter a serial number");
        this.$router.replace({ path: '/dcu/deviceconfig' });
        return false;
      }
      if (this.dbgEnablecheckbox) {
        if (this.dbgloglvlTXT === "choose Dbg Log Level" || this.dbgloglvlTXT === "") {
          this.warningMessage("Please choose any one dbg log level");
          this.$router.replace({ path: '/dcu/deviceconfig' });
          return false;
        }
        if (this.dbglogIPTXT === "" || this.dbglogIPTXT == null) {
          this.warningMessage("Please enter a dbg log ip address");
          this.$router.replace({ path: '/dcu/deviceconfig' });
          return false;
        }
        var bool22 = this.ValidateIPaddress(this.dbglogIPTXT);
        if (!bool22) {
          this.warningMessage("Dbg Log Ip invalid IP address!");
          this.$router.replace({ path: '/dcu/deviceconfig' });
          return false;
        }
      }

      if (this.lancurrIpTXT === "" || this.lancurrIpTXT == null) {
        this.warningMessage("Please enter a ethernet 1 configuration current ip address.");
        this.$router.replace({ path: '/dcu/deviceconfig' });
        return false;
      }
      var bool22 = this.ValidateIPaddress(this.lancurrIpTXT);
      if (!bool22) {
        this.warningMessage("You have entered ethernet 1 configuration current ip address is invalid IP address!");
        this.$router.replace({ path: '/dcu/deviceconfig' });
        return false;
      }
      if (this.lannewIpTXT === "" || this.lannewIpTXT == null) {
        this.warningMessage("Please enter a ethernet 1 configuration new ip address.");
        this.$router.replace({ path: '/dcu/deviceconfig' });
        return false;
      }
      var bool22 = this.ValidateIPaddress(this.lannewIpTXT);
      if (!bool22) {
        this.warningMessage("You have entered ethernet 1 configuration new ip address is invalid IP address!");
        this.$router.replace({ path: '/dcu/deviceconfig' });
        return false;
      }
      if (this.lansubnetmaskIpTXT === "" || this.lansubnetmaskIpTXT == null) {
        this.warningMessage("Please enter a ethernet 1 configuration subnet mask ip address.");
        this.$router.replace({ path: '/dcu/deviceconfig' });
        return false;
      }
      var bool22 = this.ValidateIPaddress(this.lansubnetmaskIpTXT);
      if (!bool22) {
        this.warningMessage("You have entered ethernet 1 configuration subnet mask ip address is invalid IP address!");
        this.$router.replace({ path: '/dcu/deviceconfig' });
        return false;
      }
      if (this.langatewayIpTXT === "" || this.langatewayIpTXT == null) {
        this.warningMessage("Please enter a ethernet 1 configuration gateway ip address.");
        this.$router.replace({ path: '/dcu/deviceconfig' });
        return false;
      }
      var bool22 = this.ValidateIPaddress(this.langatewayIpTXT);
      if (!bool22) {
        this.warningMessage("You have entered ethernet 1 configuration gateway ip address is invalid IP address!");
        this.$router.replace({ path: '/dcu/deviceconfig' });
        return false;
      }

      if (this.deviceCONFIGPageJSON.DATA.EthCfg.NumEthPorts == "2") {
        if (this.lancurrIp2TXT === "" || this.lancurrIp2TXT == null) {
          this.warningMessage("Please enter a ethernet 2 configuration current ip address.");
          this.$router.replace({ path: '/dcu/deviceconfig' });
          return false;
        }
        var bool22 = this.ValidateIPaddress(this.lancurrIp2TXT);
        if (!bool22) {
          this.warningMessage("You have entered ethernet 2 configuration current ip address is invalid IP address!");
          this.$router.replace({ path: '/dcu/deviceconfig' });
          return false;
        }
        if (this.lannewIp2TXT === "" || this.lannewIp2TXT == null) {
          this.warningMessage("Please enter a ethernet 2 configuration new ip address.");
          this.$router.replace({ path: '/dcu/deviceconfig' });
          return false;
        }
        var bool22 = this.ValidateIPaddress(this.lannewIp2TXT);
        if (!bool22) {
          this.warningMessage("You have entered ethernet 2 configuration new ip address is invalid IP address!");
          this.$router.replace({ path: '/dcu/deviceconfig' });
          return false;
        }
        if (this.lansubnetmaskIp2TXT === "" || this.lansubnetmaskIp2TXT == null) {
          this.warningMessage("Please enter a ethernet 2 configuration subnet mask ip address.");
          this.$router.replace({ path: '/dcu/deviceconfig' });
          return false;
        }
        var bool22 = this.ValidateIPaddress(this.lansubnetmaskIp2TXT);
        if (!bool22) {
          this.warningMessage("You have entered ethernet 2 configuration subnet mask ip address is invalid IP address!");
          this.$router.replace({ path: '/dcu/deviceconfig' });
          return false;
        }
        if (this.langatewayIp2TXT === "" || this.langatewayIp2TXT == null) {
          this.warningMessage("Please enter a ethernet 2 configuration gateway ip address.");
          this.$router.replace({ path: '/dcu/deviceconfig' });
          return false;
        }
        var bool22 = this.ValidateIPaddress(this.langatewayIp2TXT);
        if (!bool22) {
          this.warningMessage("You have entered ethernet 2 configuration gateway ip address is invalid IP address!");
          this.$router.replace({ path: '/dcu/deviceconfig' });
          return false;
        }
      }

      if (this.modemEnablechekbox) {
        if (this.modemUsernameTXT === "" || this.modemUsernameTXT == null) {
          this.warningMessage("Please enter a modem user name.");
          this.$router.replace({ path: '/dcu/deviceconfig' });
          return false;
        }
        if (this.modemPasswordTXT === "" || this.modemPasswordTXT == null) {
          this.warningMessage("Please enter a modem password.");
          this.$router.replace({ path: '/dcu/deviceconfig' });
          return false;
        }
        if (this.modemPhoneTXT === "" || this.modemPhoneTXT == null) {
          this.warningMessage("Please enter a modem phone number.");
          this.$router.replace({ path: '/dcu/deviceconfig' });
          return false;
        }
        if (this.modemAPNTXT === "" || this.modemAPNTXT == null) {
          this.warningMessage("Please enter a modem access point name.");
          this.$router.replace({ path: '/dcu/deviceconfig' });
          return false;
        }
        if (this.pingEnablenethealthchekbox) {
          if (this.modemPingIPTXT === "" || this.modemPingIPTXT == null) {
            this.warningMessage("Please enter a modem ping ip address.");
            this.$router.replace({ path: '/dcu/deviceconfig' });
            return false;
          }
          var bool22 = this.ValidateIPaddress(this.modemPingIPTXT);
          if (!bool22) {
            this.warningMessage("You have entered modem ping ip address is invalid IP address!");
            this.$router.replace({ path: '/dcu/deviceconfig' });
            return false;
          }
          if (this.modemPingIntervalTXT === "choose ping interval" || this.modemPingIntervalTXT === "") {
            this.warningMessage("Please choose any one ping interval.");
            this.$router.replace({ path: '/dcu/deviceconfig' });
            return false;
          }
          if (this.modemNumofPingTXT === "choose no of ping" || this.modemNumofPingTXT === "") {
            this.warningMessage("Please choose any one num of pings.");
            this.$router.replace({ path: '/dcu/deviceconfig' });
            return false;
          }
        }
      }

      if (this.smbEnableSMShekbox) {
        for (var mm = 0; mm < this.upstreamCONFIGjSON.DATA.SMSCfg.Details.length; mm++) {
          if (document.getElementById("smsNAMETXT" + (mm + 1)).value === "" || document.getElementById("smsNAMETXT" + (mm + 1)).value == null) {
            this.warningMessage("Please enter a modem sms user name.");
            this.$router.replace({ path: '/dcu/deviceconfig' });
            return false;
          };
          if (document.getElementById("smsphNUMTXT" + (mm + 1)).value === "" || document.getElementById("smsphNUMTXT" + (mm + 1)).value == null) {
            this.warningMessage("Please enter a modem sms user phone number.");
            this.$router.replace({ path: '/dcu/deviceconfig' });
            return false;
          };
        }
      }

      if (this.vpnEnablechekbox) {
        if (this.vpntypeTXT === 'IPSEC') {
          if (this.vpnTunnalNameTXT === "" || this.vpnTunnalNameTXT == null) {
            this.warningMessage("Please enter a vpn tunnal name.");
            this.$router.replace({ path: '/dcu/deviceconfig' });
            return false;
          }
          if (this.vpnPreSharedKeyTXT === "" || this.vpnPreSharedKeyTXT == null) {
            this.warningMessage("Please enter a vpn pre shared key.");
            this.$router.replace({ path: '/dcu/deviceconfig' });
            return false;
          }
          if (this.vpnKeyLifeTimeTXT === "" || this.vpnKeyLifeTimeTXT == null) {
            this.warningMessage("Please enter a vpn key life time.");
            this.$router.replace({ path: '/dcu/deviceconfig' });
            return false;
          }
          if (this.vpnRightIpTXT === "" || this.vpnRightIpTXT == null) {
            this.warningMessage("Please enter a vpn right ip address.");
            this.$router.replace({ path: '/dcu/deviceconfig' });
            return false;
          }
          var bool22 = this.ValidateIPaddress(this.vpnRightIpTXT);
          if (!bool22) {
            this.warningMessage("You have entered vpn right ip address is invalid IP address!");
            this.$router.replace({ path: '/dcu/deviceconfig' });
            return false;
          }
          if (this.vpnLeftSubnetTXT === "" || this.vpnLeftSubnetTXT == null) {
            this.warningMessage("Please enter a vpn right subnet address.");
            this.$router.replace({ path: '/dcu/deviceconfig' });
            return false;
          }
          var bool22 = this.ValidateIPaddress(this.vpnLeftSubnetTXT);
          if (!bool22) {
            this.warningMessage("You have entered vpn right subnet ip address is invalid IP address!");
            this.$router.replace({ path: '/dcu/deviceconfig' });
            return false;
          }
          if (this.vpnRightIdTXT === "" || this.vpnRightIdTXT == null) {
            this.warningMessage("Please enter a vpn right id.");
            this.$router.replace({ path: '/dcu/deviceconfig' });
            return false;
          }
          if (this.vpnLeftSubnetTXT === "" || this.vpnLeftSubnetTXT == null) {
            this.warningMessage("Please enter a vpn left subnet.");
            this.$router.replace({ path: '/dcu/deviceconfig' });
            return false;
          }
          var bool22 = this.ValidateIPaddress(this.vpnLeftSubnetTXT);
          if (!bool22) {
            this.warningMessage("You have entered vpn left subnet ip address is invalid IP address!");
            this.$router.replace({ path: '/dcu/deviceconfig' });
            return false;
          }
          if (this.vpnLeftIdTXT === "" || this.vpnLeftIdTXT == null) {
            this.warningMessage("Please enter a vpn left id.");
            this.$router.replace({ path: '/dcu/deviceconfig' });
            return false;
          }
          if (this.vpnPfsTXT === "" || this.vpnPfsTXT == null) {
            this.warningMessage("Please enter a vpn pfs.");
            this.$router.replace({ path: '/dcu/deviceconfig' });
            return false;
          }
          if (this.vpnAggrModeTXT === "" || this.vpnAggrModeTXT == null) {
            this.warningMessage("Please enter a vpn aggr mode.");
            this.$router.replace({ path: '/dcu/deviceconfig' });
            return false;
          }
          if (this.VpnKeyingModeTXT === "" || this.VpnKeyingModeTXT == null) {
            this.warningMessage("Please enter a vpn keying mode.");
            this.$router.replace({ path: '/dcu/deviceconfig' });
            return false;
          }
          if (this.vpnNatTravTXT === "" || this.vpnNatTravTXT == null) {
            this.warningMessage("Please enter a vpn nat trav.");
            this.$router.replace({ path: '/dcu/deviceconfig' });
            return false;
          }
          if (this.vpnDhGrpTXT === "" || this.vpnDhGrpTXT == null) {
            this.warningMessage("Please enter a vpn DhGrp1.");
            this.$router.replace({ path: '/dcu/deviceconfig' });
            return false;
          }
          if (this.vpnEncrptTXT === "" || this.vpnEncrptTXT == null) {
            this.warningMessage("Please enter a vpn Encrpt1.");
            this.$router.replace({ path: '/dcu/deviceconfig' });
            return false;
          }
          if (this.vpnAuthenTXT === "" || this.vpnAuthenTXT == null) {
            this.warningMessage("Please enter a vpn Authen1.");
            this.$router.replace({ path: '/dcu/deviceconfig' });
            return false;
          }
          if (this.vpnDhGrp2TXT === "" || this.vpnDhGrp2TXT == null) {
            this.warningMessage("Please enter a vpn DhGrp2.");
            this.$router.replace({ path: '/dcu/deviceconfig' });
            return false;
          }
          if (this.vpnEncrpt2TXT === "" || this.vpnEncrpt2TXT == null) {
            this.warningMessage("Please enter a vpn Encrpt2.");
            this.$router.replace({ path: '/dcu/deviceconfig' });
            return false;
          }
          if (this.vpnAuthen2TXT === "" || this.vpnAuthen2TXT == null) {
            this.warningMessage("Please enter a vpn Authen2.");
            this.$router.replace({ path: '/dcu/deviceconfig' });
            return false;
          }
        } else if (this.vpntypeTXT === 'PPTP') {
          if (this.vpnConnNameTXT === "" || this.vpnConnNameTXT == null) {
            this.warningMessage("Please enter a vpn connection name.");
            this.$router.replace({ path: '/dcu/deviceconfig' });
            return false;
          }
          if (this.vpnLocalUNameTXT === "" || this.vpnLocalUNameTXT == null) {
            this.warningMessage("Please enter a vpn local user name.");
            this.$router.replace({ path: '/dcu/deviceconfig' });
            return false;
          }
          if (this.vpnLocalPwdTXT === "" || this.vpnLocalPwdTXT == null) {
            this.warningMessage("Please enter a vpn local password.");
            this.$router.replace({ path: '/dcu/deviceconfig' });
            return false;
          }
          if (this.vpnRemIpTXT === "" || this.vpnRemIpTXT == null) {
            this.warningMessage("Please enter a vpn Rem Ip.");
            this.$router.replace({ path: '/dcu/deviceconfig' });
            return false;
          }
          if (this.vpnRemUNameTXT === "" || this.vpnRemUNameTXT == null) {
            this.warningMessage("Please enter a vpn Rem user name.");
            this.$router.replace({ path: '/dcu/deviceconfig' });
            return false;
          }
          if (this.vpnRemUNameTXT === "" || this.vpnRemUNameTXT == null) {
            this.warningMessage("Please enter a vpn Req_mmpe128.");
            this.$router.replace({ path: '/dcu/deviceconfig' });
            return false;
          }
        }
      }

      if (this.ntpStatedwnTXT1chekbox) {
        if (this.ntpserverIPAddressTXT1 === "" || this.ntpserverIPAddressTXT1 == null) {
          this.warningMessage("Please enter a ntp server 1 ip address.");
          this.$router.replace({ path: '/dcu/deviceconfig' });
          return false;
        }
        var bool22 = this.ValidateIPaddress(this.ntpserverIPAddressTXT1);
        if (!bool22) {
          this.warningMessage("You have entered ntp server 1 ip address is invalid IP address!");
          this.$router.replace({ path: '/dcu/deviceconfig' });
          return false;
        }
        if (this.ntpserverPortTXT1 === "" || this.ntpserverPortTXT1 == null) {
          this.warningMessage("Please enter a ntp server 1 port number.");
          this.$router.replace({ path: '/dcu/deviceconfig' });
          return false;
        }
        if (this.ntpserverPortTXT1 === "" || this.ntpserverPortTXT1 == null) {
          this.warningMessage("Please enter a ntp server 1 port number.");
          this.$router.replace({ path: '/dcu/deviceconfig' });
          return false;
        }
        if (this.ntpserverPortTXT1 <= 0 || this.ntpserverPortTXT1 > 65535) {
          this.warningMessage("ntp server 1 port number should be range 1 to 65535");
          this.$router.replace({ path: "/dcu/deviceconfig" });
          return false;
        }
      }
      if (this.ntpStatedwnTXT2chekbox) {
        if (this.ntpserverIPAddressTXT2 === "" || this.ntpserverIPAddressTXT2 == null) {
          this.warningMessage("Please enter a ntp server 2 ip address.");
          this.$router.replace({ path: '/dcu/deviceconfig' });
          return false;
        }
        var bool22 = this.ValidateIPaddress(this.ntpserverIPAddressTXT2);
        if (!bool22) {
          this.warningMessage("You have entered ntp server 2 ip address is invalid IP address!");
          this.$router.replace({ path: '/dcu/deviceconfig' });
          return false;
        }
        if (this.ntpserverPortTXT2 === "" || this.ntpserverPortTXT2 == null) {
          this.warningMessage("Please enter a ntp server 2 port number.");
          this.$router.replace({ path: '/dcu/deviceconfig' });
          return false;
        }
        if (this.ntpserverPortTXT1 <= 0 || this.ntpserverPortTXT1 > 65535) {
          this.warningMessage("ntp server 2 port number should be range 1 to 65535");
          this.$router.replace({ path: "/dcu/deviceconfig" });
          return false;
        }
      }
      if (this.ntpStatedwnTXT1chekbox || this.ntpStatedwnTXT2chekbox) {
        if (this.ntpserverIntervalTXT === "choose ntp interval" || this.ntpserverIntervalTXT === "") {
          this.warningMessage("Please choose any one ntp interval.");
          this.$router.replace({ path: '/dcu/deviceconfig' });
          return false;
        }
        if (this.ntpserverIntervalTXT <= 5 || this.ntpserverIntervalTXT > 60) {
          this.warningMessage("ntp interval minutes should be range 5 to 60");
          this.$router.replace({ path: "/dcu/deviceconfig" });
          return false;
        }
      }
    },
    smsenablefunction: function smsenablefunction() {
      var smscheck = document.getElementById('smbEnableSMShekbox').checked;
      if (!smscheck) {
        document.getElementById("smsaddBTN").style.display = "none";
        document.getElementById("smsdeleteBTN").style.display = "none";
        for (var smsIndex = 0; smsIndex < this.smsnumberDetailsArray.length; smsIndex++) {
          document.getElementById("smsNAMETXT" + (smsIndex + 1)).disabled = true;
          document.getElementById("smsNAMETXT" + (smsIndex + 1)).classList.add("disableCSS");
          document.getElementById("smsphNUMTXT" + (smsIndex + 1)).disabled = true;
          document.getElementById("smsphNUMTXT" + (smsIndex + 1)).classList.add("disableCSS");
        }
      } else {
        document.getElementById("smsaddBTN").style.display = "block";
        document.getElementById("smsdeleteBTN").style.display = "block";
        for (var smsIndex = 0; smsIndex < this.smsnumberDetailsArray.length; smsIndex++) {
          document.getElementById("smsNAMETXT" + (smsIndex + 1)).disabled = false;
          document.getElementById("smsNAMETXT" + (smsIndex + 1)).classList.remove("disableCSS");
          document.getElementById("smsphNUMTXT" + (smsIndex + 1)).disabled = false;
          document.getElementById("smsphNUMTXT" + (smsIndex + 1)).classList.remove("disableCSS");
        }
      }
    },
    addSMScount: function addSMScount() {
      if (this.smsnumberDetailsArray.length < 5) {
        this.smsnumberDetailsArray.push({ Name: '', Num: '' });
      } else {
        this.warningMessage('max 5 phone numer added only ');
        return false;
      }
    },
    deleteSMScount: function deleteSMScount() {
      if (this.smsnumberDetailsArray.length > 1) {
        this.smsnumberDetailsArray.splice(-1, 1);
      } else {
        this.warningMessage('cannot delete');
        return false;
      }
    },
    isNumber: function isNumber() {
      var event = event ? true : window.event;
      var charCode = event.which ? event.which : event.keyCode;
      if (charCode > 31 && (charCode < 48 || charCode > 57) && charCode !== 46) {
        event.preventDefault();
      } else {
        return true;
      }
    },
    validateNumberOnly: function validateNumberOnly() {
      if (event.keyCode < 48 || event.keyCode > 57) {
        event.preventDefault();
      }
    },
    ValidateIPaddress: function ValidateIPaddress(inputText) {
      var ipformat = /^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/;
      if (inputText.match(ipformat)) {
        return true;
      } else {

        return false;
      }
    },
    ValidateSubnet: function ValidateSubnet(ip) {
      var x = ip.split("."),
          x1,
          x2,
          x3,
          x4;

      if (isNotNumber(x[0]) || isNotNumber(x[1]) || isNotNumber(x[2]) || isNotNumber(x[3])) {
        return false;
      }

      if (x.length == 4) {
        x1 = parseInt(x[0], 10);
        x2 = parseInt(x[1], 10);
        x3 = parseInt(x[2], 10);
        x4 = parseInt(x[3], 10);

        if (isNaN(x1) || isNaN(x2) || isNaN(x3) || isNaN(x4)) {
          return false;
        }

        if (x1 >= 1 && x1 <= 255 && x2 >= 0 && x2 <= 255 && x3 >= 0 && x3 <= 255 && x4 >= 0 && x4 <= 255) {
          return true;
        }
      }

      return false;
    },
    checkNumber: function checkNumber(evt) {
      var evt = evt ? true : window.event;
      var charCode = evt.which ? evt.which : evt.keyCode;
      console.log('---checkNumber key-----' + charCode);
      if (charCode > 31 && (charCode < 48 || charCode > 57) && charCode !== 46) {
        evt.preventDefault();
      } else {
        return true;
      }
    },
    successMessage: function successMessage(msg) {
      this.$notice.success({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    warningMessage: function warningMessage(msg) {
      this.$notice.warning({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    infoMessage: function infoMessage(msg) {
      this.$notice.info({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    errorMessage: function errorMessage(msg) {
      this.$notice.error({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    }
  }
});

/***/ }),
/* 43 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
Object.defineProperty(__webpack_exports__, "__esModule", { value: true });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_crip_vue_notice__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_crip_vue_notice___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_0_crip_vue_notice__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_vue_element_loading__ = __webpack_require__(2);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_vue_element_loading___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_1_vue_element_loading__);




/* harmony default export */ __webpack_exports__["default"] = ({
  name: 'Changepass',
  components: {
    CripNotice: __WEBPACK_IMPORTED_MODULE_0_crip_vue_notice___default.a,
    VueElementLoading: __WEBPACK_IMPORTED_MODULE_1_vue_element_loading___default.a
  },
  data: function data() {
    return {
      isLoading: false,
      diagcategoryTXT: 'Choose Category',
      viewdataMeterDataTypeTXT: 'Choose Data Type',
      diagnosticTXTareaheight: 0,
      viewDataconfigJson: { details: [{ id: 1, date: '13-08-2020', view: '', download: '' }, { id: 2, date: '12-08-2020', view: '', download: '' }, { id: 3, date: '11-08-2020', view: '', download: '' }, { id: 4, date: '10-08-2020', view: '', download: '' }, { id: 5, date: '09-08-2020', view: '', download: '' }, { id: 6, date: '08-08-2020', view: '', download: '' }, { id: 7, date: '07-08-2020', view: '', download: '' }, { id: 8, date: '06-08-2020', view: '', download: '' }, { id: 9, date: '05-08-2020', view: '', download: '' }, { id: 10, date: '04-08-2020', view: '', download: '' }, { id: 11, date: '03-08-2020', view: '', download: '' }, { id: 12, date: '02-08-2020', view: '', download: '' }, { id: 13, date: '01-08-2020', view: '', download: '' }, { id: 14, date: '30-07-2020', view: '', download: '' }] }
    };
  },
  mounted: function mounted() {
    var _this = this;

    this.isLoading = true;
    var innerMinHeight = window.innerHeight - 125 + 'px';
    this.diagnosticTXTareaheight = window.innerHeight - 350 + 'px';
    document.getElementById('diagnosticPage').style.minHeight = innerMinHeight;
    setTimeout(function () {
      return _this.isLoading = false;
    }, 500);
  },
  created: function created() {
    if (this.$session.get("loginsession") == "") {
      this.$router.replace({ path: '/' });
      return false;
    }
  },

  methods: {
    isNumber: function isNumber(evt) {
      evt = evt ? true : window.event;
      var charCode = evt.which ? evt.which : evt.keyCode;
      if (charCode > 31 && (charCode < 48 || charCode > 57) && charCode !== 46) {
        evt.preventDefault();
      } else {
        return true;
      }
    },
    successMessage: function successMessage(msg) {
      this.$notice.success({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    warningMessage: function warningMessage(msg) {
      this.$notice.warning({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    infoMessage: function infoMessage(msg) {
      this.$notice.info({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    errorMessage: function errorMessage(msg) {
      this.$notice.error({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    }
  }
});

/***/ }),
/* 44 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
Object.defineProperty(__webpack_exports__, "__esModule", { value: true });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify__ = __webpack_require__(3);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_crip_vue_notice__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_crip_vue_notice___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_1_crip_vue_notice__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2_vue_element_loading__ = __webpack_require__(2);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2_vue_element_loading___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_2_vue_element_loading__);





/* harmony default export */ __webpack_exports__["default"] = ({
  name: 'MeterConfig',
  components: {
    CripNotice: __WEBPACK_IMPORTED_MODULE_1_crip_vue_notice___default.a,
    VueElementLoading: __WEBPACK_IMPORTED_MODULE_2_vue_element_loading___default.a
  },
  data: function data() {
    return {
      deviceCONFIGPageJSON: this.$session.get("get_GenconfigJSON"),
      upstreamCONFIGPageJSON: this.$session.get("get_UpstreamconfigJSON"),
      meterCONFIGPageJSON: this.$session.get("get_DlmsMeterconfigSON"),
      masterINSTCONFIGPageJSON: this.$session.get("get_MasterINSTJSON"),
      masterLSCONFIGPageJSON: this.$session.get("get_MasterLSJSON"),
      masterMNCONFIGPageJSON: this.$session.get("get_MasterMNJSON"),
      masterEVENTCONFIGPageJSON: this.$session.get("get_MasterEVENTJSON"),
      masterBILLCONFIGPageJSON: this.$session.get("get_MasterBILLJSON"),
      selectINSTCONFIGPageJSON: this.$session.get("get_SelectedINSTJSON"),
      selectLSCONFIGPageJSON: this.$session.get("get_SelectedLSJSON"),
      selectMNCONFIGPageJSON: this.$session.get("get_SelectedMNJSON"),
      selectEVENTCONFIGPageJSON: this.$session.get("get_SelectedEVENTJSON"),
      selectBILLCONFIGPageJSON: this.$session.get("get_SelectedBILLJSON"),
      isLoading: false,
      tableheight: 0,
      tableheight1: 0,
      instantaneousETHchekbox: true,
      loadserveETHchekbox: true,
      eventdataETHchekbox: true,
      midnightETHchekbox: false,
      billingETHchekbox: false,
      midnightETHpollPeroidTXT: '',
      billingETHpollPeroidTXT: '',
      instantaneousSERIALchekbox: true,
      loadserveSERIALchekbox: true,
      eventdataSERIALchekbox: true,
      midnightSERIALchekbox: false,
      billingSERIALchekbox: false,
      midnightSERIALpollPeroidTXT: '',
      billingSERIALpollPeroidTXT: '',
      instantaneousFAULTchekbox: true,
      loadserveFAULTchekbox: true,
      eventdataFAULTchekbox: true,
      midnightFAULTchekbox: false,
      billingFAULTchekbox: false,
      midnightFAULTpollPeroidTXT: '',
      billingFAULTpollPeroidTXT: '',
      addressSZIEArray: ["1", "2", "4"]
    };
  },
  mounted: function mounted() {
    var _this = this;

    this.isLoading = true;
    var innerMinHeight = window.innerHeight - 125 + 'px';
    this.tableheight = window.innerHeight - 245 + 'px';
    this.tableheight1 = window.innerHeight - 485 + 'px';
    document.getElementById('meterconfigpane').style.minHeight = innerMinHeight;
    setTimeout(function () {
      return _this.isLoading = false;
    }, 500);
    this.loadMeterConfigPage();
  },
  created: function created() {
    if (this.$session.get("loginsession") == "") {
      this.$router.replace({ path: '/' });
      return false;
    }
  },
  updated: function updated() {
    this.saveMeterConfigPage();
  },

  methods: {
    serialNOcommMOde: function serialNOcommMOde(id, rowIndex) {
      console.log('--DLMSP---', __WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(this.meterCONFIGPageJSON.DATA['DLMSP' + (rowIndex - 1) + 'MetCfg'].Meters));
      if (document.getElementById(id).value == "RS232_MODE") {
        console.log('---------IF---------');
        this.addressSZIEArray = [];
        this.addressSZIEArray = ["1"];
        this.meterCONFIGPageJSON.DATA['DLMSP' + (rowIndex - 1) + 'MetCfg'].Meters.length = 1;
      } else {
        this.addressSZIEArray = [];
        this.addressSZIEArray = ["1", "2", "4"];
        console.log('---------ELSE---------');
        this.meterCONFIGPageJSON.DATA['DLMSP' + (rowIndex - 1) + 'MetCfg'].Meters.length = 5;
      }
    },
    loadMeterConfigPage: function loadMeterConfigPage() {
      if (this.meterCONFIGPageJSON.DATA.DLMSCfg.MeterType == 'Ethernet') {
        this.instantaneousETHchekbox = this.meterCONFIGPageJSON.DATA.DLMSCfg.EnableInstData == 'No' ? false : true;
        this.loadserveETHchekbox = this.meterCONFIGPageJSON.DATA.DLMSCfg.EnableLSData == 'No' ? false : true;
        this.eventdataETHchekbox = this.meterCONFIGPageJSON.DATA.DLMSCfg.EnableEventData == 'No' ? false : true;
        this.midnightETHchekbox = this.meterCONFIGPageJSON.DATA.DLMSCfg.EnableMidnightData == 'No' ? false : true;
        this.billingETHchekbox = this.meterCONFIGPageJSON.DATA.DLMSCfg.EnableBillingData == 'No' ? false : true;
        this.midnightETHpollPeroidTXT = this.meterCONFIGPageJSON.DATA.DLMSCfg.MidnightPollPer;
        this.billingETHpollPeroidTXT = this.meterCONFIGPageJSON.DATA.DLMSCfg.BillingPollPer;
      } else if (this.meterCONFIGPageJSON.DATA.DLMSCfg.MeterType == 'Serial' && this.meterCONFIGPageJSON.DATA.DLMSCfg.FaultTolSupp == 'No') {
        this.instantaneousSERIALchekbox = this.meterCONFIGPageJSON.DATA.DLMSCfg.EnableInstData == 'No' ? false : true;
        this.loadserveSERIALchekbox = this.meterCONFIGPageJSON.DATA.DLMSCfg.EnableLSData == 'No' ? false : true;
        this.eventdataSERIALchekbox = this.meterCONFIGPageJSON.DATA.DLMSCfg.EnableEventData == 'No' ? false : true;
        this.midnightSERIALchekbox = this.meterCONFIGPageJSON.DATA.DLMSCfg.EnableMidnightData == 'No' ? false : true;
        this.billingSERIALchekbox = this.meterCONFIGPageJSON.DATA.DLMSCfg.EnableBillingData == 'No' ? false : true;
        this.midnightSERIALpollPeroidTXT = this.meterCONFIGPageJSON.DATA.DLMSCfg.MidnightPollPer;
        this.billingSERIALpollPeroidTXT = this.meterCONFIGPageJSON.DATA.DLMSCfg.BillingPollPer;
        for (var portindex = 0; portindex < parseInt(this.deviceCONFIGPageJSON.DATA.SerPortCfg.NumSerPorts); portindex++) {
          document.getElementById('commModeDrpDwnID_serialportTabPANE' + (portindex + 1)).value = this.deviceCONFIGPageJSON.DATA.SerPortCfg.PortCfg[portindex].InfMode;

          document.getElementById('baudrateeDrpDwnID_serialportTabPANE' + (portindex + 1)).value = this.deviceCONFIGPageJSON.DATA.SerPortCfg.PortCfg[portindex].BaudRate;
          document.getElementById('stopbitsDrpDwnID_serialportTabPANE' + (portindex + 1)).value = this.deviceCONFIGPageJSON.DATA.SerPortCfg.PortCfg[portindex].Stopbits;
          document.getElementById('partyDrpDwnTID_serialportTabPANE' + (portindex + 1)).value = this.deviceCONFIGPageJSON.DATA.SerPortCfg.PortCfg[portindex].Parity;
          document.getElementById('databitsDrpDwnID_serialportTabPANE' + (portindex + 1)).value = this.deviceCONFIGPageJSON.DATA.SerPortCfg.PortCfg[portindex].Databits;
        }
      } else if (this.meterCONFIGPageJSON.DATA.DLMSCfg.MeterType == 'Serial' && this.meterCONFIGPageJSON.DATA.DLMSCfg.FaultTolSupp == 'Yes') {
        this.instantaneousFAULTchekbox = this.meterCONFIGPageJSON.DATA.DLMSCfg.EnableInstData == 'No' ? false : true;
        this.loadserveFAULTchekbox = this.meterCONFIGPageJSON.DATA.DLMSCfg.EnableLSData == 'No' ? false : true;
        this.eventdataFAULTchekbox = this.meterCONFIGPageJSON.DATA.DLMSCfg.EnableEventData == 'No' ? false : true;
        this.midnightFAULTchekbox = this.meterCONFIGPageJSON.DATA.DLMSCfg.EnableMidnightData == 'No' ? false : true;
        this.billingFAULTchekbox = this.meterCONFIGPageJSON.DATA.DLMSCfg.EnableBillingData == 'No' ? false : true;
        this.midnightFAULTpollPeroidTXT = this.meterCONFIGPageJSON.DATA.DLMSCfg.MidnightPollPer;
        this.billingFAULTpollPeroidTXT = this.meterCONFIGPageJSON.DATA.DLMSCfg.BillingPollPer;
        for (var portindex = 0; portindex < parseInt(this.deviceCONFIGPageJSON.DATA.SerPortCfg.NumSerPorts); portindex++) {
          document.getElementById('commModeDrpDwnID_faultportTabPANE' + (portindex + 1)).value = this.deviceCONFIGPageJSON.DATA.SerPortCfg.PortCfg[portindex].InfMode;

          document.getElementById('baudrateeDrpDwnID_faultportTabPANE' + (portindex + 1)).value = this.deviceCONFIGPageJSON.DATA.SerPortCfg.PortCfg[portindex].BaudRate;
          document.getElementById('stopbitsDrpDwnID_faultportTabPANE' + (portindex + 1)).value = this.deviceCONFIGPageJSON.DATA.SerPortCfg.PortCfg[portindex].Stopbits;
          document.getElementById('partyDrpDwnTID_faultportTabPANE' + (portindex + 1)).value = this.deviceCONFIGPageJSON.DATA.SerPortCfg.PortCfg[portindex].Parity;
          document.getElementById('databitsDrpDwnID_faultportTabPANE' + (portindex + 1)).value = this.deviceCONFIGPageJSON.DATA.SerPortCfg.PortCfg[portindex].Databits;
        }
      }
    },
    saveMeterConfigPage: function saveMeterConfigPage() {
      if (this.meterCONFIGPageJSON.DATA.DLMSCfg.MeterType == 'Ethernet') {
        this.meterCONFIGPageJSON.DATA.DLMSCfg.EnableInstData = this.instantaneousETHchekbox == true ? "Yes" : "No";
        this.meterCONFIGPageJSON.DATA.DLMSCfg.EnableLSData = this.loadserveETHchekbox == true ? "Yes" : "No";
        this.meterCONFIGPageJSON.DATA.DLMSCfg.EnableEventData = this.eventdataETHchekbox == true ? "Yes" : "No";
        this.meterCONFIGPageJSON.DATA.DLMSCfg.EnableMidnightData = this.midnightETHchekbox == true ? "Yes" : "No";
        this.meterCONFIGPageJSON.DATA.DLMSCfg.EnableBillingData = this.billingETHchekbox == true ? "Yes" : "No";
        this.meterCONFIGPageJSON.DATA.DLMSCfg.MidnightPollPer = this.midnightETHpollPeroidTXT;
        this.meterCONFIGPageJSON.DATA.DLMSCfg.BillingPollPer = this.billingETHpollPeroidTXT;
        var enthlength = parseInt(this.meterCONFIGPageJSON.DATA.DLMSEthMetCfg.NumMeters);
        if (enthlength != 0) {
          for (var kk = 0; kk < enthlength; kk++) {
            this.meterCONFIGPageJSON.DATA.DLMSEthMetCfg.EthMeters[kk].Enable = document.getElementById("ethnetcheckbox" + (kk + 1)).checked == true ? "1" : "0";
            this.meterCONFIGPageJSON.DATA.DLMSEthMetCfg.EthMeters[kk].Ip = document.getElementById("ethnetipaddress" + (kk + 1)).value;
            this.meterCONFIGPageJSON.DATA.DLMSEthMetCfg.EthMeters[kk].Port = document.getElementById("ethnetport" + (kk + 1)).value;
            this.meterCONFIGPageJSON.DATA.DLMSEthMetCfg.EthMeters[kk].Pwd = document.getElementById("ethnetPwd" + (kk + 1)).value;
            this.meterCONFIGPageJSON.DATA.DLMSEthMetCfg.EthMeters[kk].Loc = document.getElementById("ethnetLoc" + (kk + 1)).value;
            this.meterCONFIGPageJSON.DATA.DLMSEthMetCfg.EthMeters[kk].TO = document.getElementById("ethnetTO" + (kk + 1)).value;
            this.meterCONFIGPageJSON.DATA.DLMSEthMetCfg.EthMeters[kk].RetCnt = document.getElementById("ethnetRetCnt" + (kk + 1)).value;
          }
        }
      } else if (this.meterCONFIGPageJSON.DATA.DLMSCfg.MeterType == 'Serial' && this.meterCONFIGPageJSON.DATA.DLMSCfg.FaultTolSupp == 'No') {
        this.meterCONFIGPageJSON.DATA.DLMSCfg.EnableInstData = this.instantaneousSERIALchekbox == true ? "Yes" : "No";
        this.meterCONFIGPageJSON.DATA.DLMSCfg.EnableLSData = this.loadserveSERIALchekbox == true ? "Yes" : "No";
        this.meterCONFIGPageJSON.DATA.DLMSCfg.EnableEventData = this.eventdataSERIALchekbox == true ? "Yes" : "No";
        this.meterCONFIGPageJSON.DATA.DLMSCfg.EnableMidnightData = this.midnightSERIALchekbox == true ? "Yes" : "No";
        this.meterCONFIGPageJSON.DATA.DLMSCfg.EnableBillingData = this.billingSERIALchekbox == true ? "Yes" : "No";
        this.meterCONFIGPageJSON.DATA.DLMSCfg.MidnightPollPer = this.midnightSERIALpollPeroidTXT;
        this.meterCONFIGPageJSON.DATA.DLMSCfg.BillingPollPer = this.billingSERIALpollPeroidTXT;
        for (var portindex = 0; portindex < parseInt(this.deviceCONFIGPageJSON.DATA.SerPortCfg.NumSerPorts); portindex++) {
          this.deviceCONFIGPageJSON.DATA.SerPortCfg.PortCfg[portindex].InfMode = document.getElementById('commModeDrpDwnID_serialportTabPANE' + (portindex + 1)).value;

          this.deviceCONFIGPageJSON.DATA.SerPortCfg.PortCfg[portindex].BaudRate = document.getElementById('baudrateeDrpDwnID_serialportTabPANE' + (portindex + 1)).value;
          this.deviceCONFIGPageJSON.DATA.SerPortCfg.PortCfg[portindex].Stopbits = document.getElementById('stopbitsDrpDwnID_serialportTabPANE' + (portindex + 1)).value;
          this.deviceCONFIGPageJSON.DATA.SerPortCfg.PortCfg[portindex].Parity = document.getElementById('partyDrpDwnTID_serialportTabPANE' + (portindex + 1)).value;
          this.deviceCONFIGPageJSON.DATA.SerPortCfg.PortCfg[portindex].Databits = document.getElementById('databitsDrpDwnID_serialportTabPANE' + (portindex + 1)).value;
        }
        var enthlength = parseInt(this.deviceCONFIGPageJSON.DATA.SerPortCfg.NumSerPorts);
        if (enthlength != 0) {
          for (var tt = 0; tt < enthlength; tt++) {
            for (var mm = 0; mm < this.meterCONFIGPageJSON.DATA['DLMSP' + tt + 'MetCfg'].Meters.length; mm++) {
              this.meterCONFIGPageJSON.DATA['DLMSP' + tt + 'MetCfg'].Meters[mm].Enable = document.getElementById("portSERIALcheckboxDLMSP" + tt + 'MetCfg' + (mm + 1)).checked == true ? "1" : "0";
              this.meterCONFIGPageJSON.DATA['DLMSP' + tt + 'MetCfg'].Meters[mm].Addr = document.getElementById("portSERIALaddressDLMSP" + tt + 'MetCfg' + (mm + 1)).value;
              this.meterCONFIGPageJSON.DATA['DLMSP' + tt + 'MetCfg'].Meters[mm].AddrSz = document.getElementById("portSERIALaddsizeDLMSP" + tt + 'MetCfg' + (mm + 1)).value;
              this.meterCONFIGPageJSON.DATA['DLMSP' + tt + 'MetCfg'].Meters[mm].Pwd = document.getElementById("portSERIALPWDDLMSP" + tt + 'MetCfg' + (mm + 1)).value;
              this.meterCONFIGPageJSON.DATA['DLMSP' + tt + 'MetCfg'].Meters[mm].Loc = document.getElementById("portSERIALLocDLMSP" + tt + 'MetCfg' + (mm + 1)).value;
              this.meterCONFIGPageJSON.DATA['DLMSP' + tt + 'MetCfg'].Meters[mm].TO = document.getElementById("portSERIALToDLMSP" + tt + 'MetCfg' + (mm + 1)).value;
              this.meterCONFIGPageJSON.DATA['DLMSP' + tt + 'MetCfg'].Meters[mm].RetCnt = document.getElementById("portSERIALRetCntDLMSP" + tt + 'MetCfg' + (mm + 1)).value;
            }
          }
        }
      } else if (this.meterCONFIGPageJSON.DATA.DLMSCfg.MeterType == 'Serial' && this.meterCONFIGPageJSON.DATA.DLMSCfg.FaultTolSupp == 'Yes') {
        this.meterCONFIGPageJSON.DATA.DLMSCfg.EnableInstData = this.instantaneousFAULTchekbox == true ? "Yes" : "No";
        this.meterCONFIGPageJSON.DATA.DLMSCfg.EnableLSData = this.loadserveFAULTchekbox == true ? "Yes" : "No";
        this.meterCONFIGPageJSON.DATA.DLMSCfg.EnableEventData = this.eventdataFAULTchekbox == true ? "Yes" : "No";
        this.meterCONFIGPageJSON.DATA.DLMSCfg.EnableMidnightData = this.midnightFAULTchekbox == true ? "Yes" : "No";
        this.meterCONFIGPageJSON.DATA.DLMSCfg.EnableBillingData = this.billingFAULTchekbox == true ? "Yes" : "No";
        this.meterCONFIGPageJSON.DATA.DLMSCfg.MidnightPollPer = this.midnightFAULTpollPeroidTXT;
        this.meterCONFIGPageJSON.DATA.DLMSCfg.BillingPollPer = this.billingFAULTpollPeroidTXT;
        for (var portindex = 0; portindex < parseInt(this.deviceCONFIGPageJSON.DATA.SerPortCfg.NumSerPorts); portindex++) {
          this.deviceCONFIGPageJSON.DATA.SerPortCfg.PortCfg[portindex].InfMode = document.getElementById('commModeDrpDwnID_faultportTabPANE' + (portindex + 1)).value;

          this.deviceCONFIGPageJSON.DATA.SerPortCfg.PortCfg[portindex].BaudRate = document.getElementById('baudrateeDrpDwnID_faultportTabPANE' + (portindex + 1)).value;
          this.deviceCONFIGPageJSON.DATA.SerPortCfg.PortCfg[portindex].Stopbits = document.getElementById('stopbitsDrpDwnID_faultportTabPANE' + (portindex + 1)).value;
          this.deviceCONFIGPageJSON.DATA.SerPortCfg.PortCfg[portindex].Parity = document.getElementById('partyDrpDwnTID_faultportTabPANE' + (portindex + 1)).value;
          this.deviceCONFIGPageJSON.DATA.SerPortCfg.PortCfg[portindex].Databits = document.getElementById('databitsDrpDwnID_faultportTabPANE' + (portindex + 1)).value;
        }
        var enthlength = parseInt(this.deviceCONFIGPageJSON.DATA.SerPortCfg.NumSerPorts);
        if (enthlength != 0) {
          for (var tt = 0; tt < enthlength; tt++) {
            for (var mm = 0; mm < this.meterCONFIGPageJSON.DATA['DLMSP' + tt + 'MetCfg'].Meters.length; mm++) {
              this.meterCONFIGPageJSON.DATA['DLMSP' + tt + 'MetCfg'].Meters[mm].Enable = document.getElementById("portFAULTcheckboxDLMSP" + tt + 'MetCfg' + (mm + 1)).checked == true ? "1" : "0";
              this.meterCONFIGPageJSON.DATA['DLMSP' + tt + 'MetCfg'].Meters[mm].Addr = document.getElementById("portFAULTaddrDLMSP" + tt + 'MetCfg' + (mm + 1)).value;
              this.meterCONFIGPageJSON.DATA['DLMSP' + tt + 'MetCfg'].Meters[mm].AddrType = document.getElementById("portFAULTAddrTypeDLMSP" + tt + 'MetCfg' + (mm + 1)).value;
              this.meterCONFIGPageJSON.DATA['DLMSP' + tt + 'MetCfg'].Meters[mm].Pwd = document.getElementById("portFAULTPwdDLMSP" + tt + 'MetCfg' + (mm + 1)).value;
              this.meterCONFIGPageJSON.DATA['DLMSP' + tt + 'MetCfg'].Meters[mm].Loc = document.getElementById("portFAULTLocDLMSP" + tt + 'MetCfg' + (mm + 1)).value;
              this.meterCONFIGPageJSON.DATA['DLMSP' + tt + 'MetCfg'].Meters[mm].TO = document.getElementById("portFAULTTODLMSP" + tt + 'MetCfg' + (mm + 1)).value;
              this.meterCONFIGPageJSON.DATA['DLMSP' + tt + 'MetCfg'].Meters[mm].RetCnt = document.getElementById("portFAULTRetCntDLMSP" + tt + 'MetCfg' + (mm + 1)).value;
            }
          }
        }
      }
      this.$session.set('get_GenconfigJSON', this.deviceCONFIGPageJSON);
      this.$session.set('get_DlmsMeterconfigSON', this.meterCONFIGPageJSON);
    },
    addETHmeterBTN: function addETHmeterBTN() {
      if (this.meterCONFIGPageJSON.DATA['DLMSEthMetCfg'].EthMeters.length >= parseInt(this.meterCONFIGPageJSON.DATA.DLMSCfg.MaxMeters)) {
        this.warningMessage('Not allow to add meter');
        return false;
      }
      var addobject = { "Enable": "1", "Ip": "sssssssssssssss", "Port": "2345", "Pwd": "lnt1", "Loc": "Meter_1", "TO": "2", "RetCnt": "3" };
      this.meterCONFIGPageJSON.DATA['DLMSEthMetCfg'].NumMeters = this.meterCONFIGPageJSON.DATA['DLMSEthMetCfg'].EthMeters.length.toString();
      this.meterCONFIGPageJSON.DATA['DLMSEthMetCfg'].EthMeters.push(addobject);
    },
    deleteETHTBTN: function deleteETHTBTN(index, inputItems) {
      this.meterCONFIGPageJSON.DATA['DLMSEthMetCfg'].EthMeters.splice(index, 1);
      this.meterCONFIGPageJSON.DATA['DLMSEthMetCfg'].NumMeters = this.meterCONFIGPageJSON.DATA['DLMSEthMetCfg'].EthMeters.length.toString();
    },
    addmeterSERIAL: function addmeterSERIAL(id, portIndex) {
      if (this.meterCONFIGPageJSON.DATA['DLMSP' + (portIndex - 1) + 'MetCfg'].Meters.length >= parseInt(this.meterCONFIGPageJSON.DATA.DLMSCfg.MaxMeters)) {
        this.warningMessage('Not allow to add meter');
        return false;
      }
      var addobject = { "Enable": "1", "Addr": "18", "AddrSz": "2", "Pwd": "lnt1", "Loc": "Meter_1", "TO": "2", "RetCnt": "3" };
      this.meterCONFIGPageJSON.DATA['DLMSP' + (portIndex - 1) + 'MetCfg'].NumMeters = this.meterCONFIGPageJSON.DATA['DLMSP' + (portIndex - 1) + 'MetCfg'].Meters.length.toString();
      this.meterCONFIGPageJSON.DATA['DLMSP' + (portIndex - 1) + 'MetCfg'].Meters.push(addobject);
    },
    deleteSERIALBTN: function deleteSERIALBTN(rowIndex, portIndex, resultobj) {
      this.meterCONFIGPageJSON.DATA['DLMSP' + portIndex + 'MetCfg'].Meters.splice(rowIndex, 1);
      this.meterCONFIGPageJSON.DATA['DLMSP' + portIndex + 'MetCfg'].NumMeters = this.meterCONFIGPageJSON.DATA['DLMSP' + portIndex + 'MetCfg'].Meters.length.toString();
    },
    addmeterFAULT: function addmeterFAULT(id, portIndex) {
      if (this.meterCONFIGPageJSON.DATA['DLMSP' + (portIndex - 1) + 'MetCfg'].Meters.length >= parseInt(this.meterCONFIGPageJSON.DATA.DLMSCfg.MaxMeters)) {
        this.warningMessage('Not allow to add meter');
        return false;
      }
      var addobject = { "Enable": "1", "Addr": "18", "AddrSz": "2", "Pwd": "lnt1", "Loc": "Meter_1", "TO": "2", "RetCnt": "3" };
      this.meterCONFIGPageJSON.DATA['DLMSP' + (portIndex - 1) + 'MetCfg'].NumMeters = this.meterCONFIGPageJSON.DATA['DLMSP' + (portIndex - 1) + 'MetCfg'].Meters.length.toString();
      this.meterCONFIGPageJSON.DATA['DLMSP' + (portIndex - 1) + 'MetCfg'].Meters.push(addobject);
    },
    deleteFAULTBTN: function deleteFAULTBTN(rowIndex, portIndex, resultobj) {
      this.meterCONFIGPageJSON.DATA['DLMSP' + portIndex + 'MetCfg'].Meters.splice(rowIndex, 1);
      this.meterCONFIGPageJSON.DATA['DLMSP' + portIndex + 'MetCfg'].NumMeters = this.meterCONFIGPageJSON.DATA['DLMSP' + portIndex + 'MetCfg'].Meters.length.toString();
    },
    enableSERIALMeterdevice: function enableSERIALMeterdevice(event, configIndex, tablerowIndex, selObj) {
      var element = event.target;
      var eleId = element.getAttribute('id');
      var portmetercheckboxVal = document.getElementById("portSERIALcheckboxDLMSP" + configIndex + "MetCfg" + tablerowIndex).checked;
      if (portmetercheckboxVal) {
        var elem = document.getElementById("portSERIALaddressDLMSP" + configIndex + "MetCfg" + tablerowIndex);
        if (typeof elem !== 'undefined' && elem !== null) {
          document.getElementById("portSERIALaddressDLMSP" + configIndex + "MetCfg" + tablerowIndex).disabled = false;
          document.getElementById("portSERIALaddressDLMSP" + configIndex + "MetCfg" + tablerowIndex).classList.remove("disableCSS");
        }
        var elem = document.getElementById("portSERIALaddsizeDLMSP" + configIndex + "MetCfg" + tablerowIndex);
        if (typeof elem !== 'undefined' && elem !== null) {
          document.getElementById("portSERIALaddsizeDLMSP" + configIndex + "MetCfg" + tablerowIndex).disabled = false;
          document.getElementById("portSERIALaddsizeDLMSP" + configIndex + "MetCfg" + tablerowIndex).classList.remove("disableCSS");
        }
        var elem = document.getElementById("portSERIALPWDDLMSP" + configIndex + "MetCfg" + tablerowIndex);
        if (typeof elem !== 'undefined' && elem !== null) {
          document.getElementById("portSERIALPWDDLMSP" + configIndex + "MetCfg" + tablerowIndex).disabled = false;
          document.getElementById("portSERIALPWDDLMSP" + configIndex + "MetCfg" + tablerowIndex).classList.remove("disableCSS");
        }
        var elem = document.getElementById("portSERIALLocDLMSP" + configIndex + "MetCfg" + tablerowIndex);
        if (typeof elem !== 'undefined' && elem !== null) {
          document.getElementById("portSERIALLocDLMSP" + configIndex + "MetCfg" + tablerowIndex).disabled = false;
          document.getElementById("portSERIALLocDLMSP" + configIndex + "MetCfg" + tablerowIndex).classList.remove("disableCSS");
        }
        var elem = document.getElementById("portSERIALToDLMSP" + configIndex + "MetCfg" + tablerowIndex);
        if (typeof elem !== 'undefined' && elem !== null) {
          document.getElementById("portSERIALToDLMSP" + configIndex + "MetCfg" + tablerowIndex).disabled = false;
          document.getElementById("portSERIALToDLMSP" + configIndex + "MetCfg" + tablerowIndex).classList.remove("disableCSS");
        }
        var elem = document.getElementById("portSERIALRetCntDLMSP" + configIndex + "MetCfg" + tablerowIndex);
        if (typeof elem !== 'undefined' && elem !== null) {
          document.getElementById("portSERIALRetCntDLMSP" + configIndex + "MetCfg" + tablerowIndex).disabled = false;
          document.getElementById("portSERIALRetCntDLMSP" + configIndex + "MetCfg" + tablerowIndex).classList.remove("disableCSS");
        }
      } else {
        var elem = document.getElementById("portSERIALaddressDLMSP" + configIndex + "MetCfg" + tablerowIndex);
        if (typeof elem !== 'undefined' && elem !== null) {
          document.getElementById("portSERIALaddressDLMSP" + configIndex + "MetCfg" + tablerowIndex).disabled = true;
          document.getElementById("portSERIALaddressDLMSP" + configIndex + "MetCfg" + tablerowIndex).classList.add("disableCSS");
        }
        var elem = document.getElementById("portSERIALaddsizeDLMSP" + configIndex + "MetCfg" + tablerowIndex);
        if (typeof elem !== 'undefined' && elem !== null) {
          document.getElementById("portSERIALaddsizeDLMSP" + configIndex + "MetCfg" + tablerowIndex).disabled = true;
          document.getElementById("portSERIALaddsizeDLMSP" + configIndex + "MetCfg" + tablerowIndex).classList.add("disableCSS");
        }
        var elem = document.getElementById("portSERIALPWDDLMSP" + configIndex + "MetCfg" + tablerowIndex);
        if (typeof elem !== 'undefined' && elem !== null) {
          document.getElementById("portSERIALPWDDLMSP" + configIndex + "MetCfg" + tablerowIndex).disabled = true;
          document.getElementById("portSERIALPWDDLMSP" + configIndex + "MetCfg" + tablerowIndex).classList.add("disableCSS");
        }
        var elem = document.getElementById("portSERIALLocDLMSP" + configIndex + "MetCfg" + tablerowIndex);
        if (typeof elem !== 'undefined' && elem !== null) {
          document.getElementById("portSERIALLocDLMSP" + configIndex + "MetCfg" + tablerowIndex).disabled = true;
          document.getElementById("portSERIALLocDLMSP" + configIndex + "MetCfg" + tablerowIndex).classList.add("disableCSS");
        }
        var elem = document.getElementById("portSERIALToDLMSP" + configIndex + "MetCfg" + tablerowIndex);
        if (typeof elem !== 'undefined' && elem !== null) {
          document.getElementById("portSERIALToDLMSP" + configIndex + "MetCfg" + tablerowIndex).disabled = true;
          document.getElementById("portSERIALToDLMSP" + configIndex + "MetCfg" + tablerowIndex).classList.add("disableCSS");
        }
        var elem = document.getElementById("portSERIALRetCntDLMSP" + configIndex + "MetCfg" + tablerowIndex);
        if (typeof elem !== 'undefined' && elem !== null) {
          document.getElementById("portSERIALRetCntDLMSP" + configIndex + "MetCfg" + tablerowIndex).disabled = true;
          document.getElementById("portSERIALRetCntDLMSP" + configIndex + "MetCfg" + tablerowIndex).classList.add("disableCSS");
        }
      }
      this.saveMeterConfigPage();
    },
    enableFAULTdevice: function enableFAULTdevice(event, configIndex, tablerowIndex, selObj) {
      var element = event.target;
      var eleId = element.getAttribute('id');
      var portmetercheckboxVal = document.getElementById("portFAULTcheckboxDLMSP" + configIndex + "MetCfg" + tablerowIndex).checked;
      if (portmetercheckboxVal) {
        var elem = document.getElementById("portFAULTaddrDLMSP" + configIndex + "MetCfg" + tablerowIndex);
        if (typeof elem !== 'undefined' && elem !== null) {
          document.getElementById("portFAULTaddrDLMSP" + configIndex + "MetCfg" + tablerowIndex).disabled = false;
          document.getElementById("portFAULTaddrDLMSP" + configIndex + "MetCfg" + tablerowIndex).classList.remove("disableCSS");
        }
        var elem = document.getElementById("portFAULTAddrTypeDLMSP" + configIndex + "MetCfg" + tablerowIndex);
        if (typeof elem !== 'undefined' && elem !== null) {
          document.getElementById("portFAULTAddrTypeDLMSP" + configIndex + "MetCfg" + tablerowIndex).disabled = false;
          document.getElementById("portFAULTAddrTypeDLMSP" + configIndex + "MetCfg" + tablerowIndex).classList.remove("disableCSS");
        }
        var elem = document.getElementById("portFAULTPwdDLMSP" + configIndex + "MetCfg" + tablerowIndex);
        if (typeof elem !== 'undefined' && elem !== null) {
          document.getElementById("portFAULTPwdDLMSP" + configIndex + "MetCfg" + tablerowIndex).disabled = false;
          document.getElementById("portFAULTPwdDLMSP" + configIndex + "MetCfg" + tablerowIndex).classList.remove("disableCSS");
        }
        var elem = document.getElementById("portFAULTLocDLMSP" + configIndex + "MetCfg" + tablerowIndex);
        if (typeof elem !== 'undefined' && elem !== null) {
          document.getElementById("portFAULTLocDLMSP" + configIndex + "MetCfg" + tablerowIndex).disabled = false;
          document.getElementById("portFAULTLocDLMSP" + configIndex + "MetCfg" + tablerowIndex).classList.remove("disableCSS");
        }
        var elem = document.getElementById("portFAULTTODLMSP" + configIndex + "MetCfg" + tablerowIndex);
        if (typeof elem !== 'undefined' && elem !== null) {
          document.getElementById("portFAULTTODLMSP" + configIndex + "MetCfg" + tablerowIndex).disabled = false;
          document.getElementById("portFAULTTODLMSP" + configIndex + "MetCfg" + tablerowIndex).classList.remove("disableCSS");
        }
        var elem = document.getElementById("portFAULTRetCntDLMSP" + configIndex + "MetCfg" + tablerowIndex);
        if (typeof elem !== 'undefined' && elem !== null) {
          document.getElementById("portFAULTRetCntDLMSP" + configIndex + "MetCfg" + tablerowIndex).disabled = false;
          document.getElementById("portFAULTRetCntDLMSP" + configIndex + "MetCfg" + tablerowIndex).classList.remove("disableCSS");
        }
      } else {
        var elem = document.getElementById("portFAULTaddrDLMSP" + configIndex + "MetCfg" + tablerowIndex);
        if (typeof elem !== 'undefined' && elem !== null) {
          document.getElementById("portFAULTaddrDLMSP" + configIndex + "MetCfg" + tablerowIndex).disabled = true;
          document.getElementById("portFAULTaddrDLMSP" + configIndex + "MetCfg" + tablerowIndex).classList.add("disableCSS");
        }
        var elem = document.getElementById("portFAULTAddrTypeDLMSP" + configIndex + "MetCfg" + tablerowIndex);
        if (typeof elem !== 'undefined' && elem !== null) {
          document.getElementById("portFAULTAddrTypeDLMSP" + configIndex + "MetCfg" + tablerowIndex).disabled = true;
          document.getElementById("portFAULTAddrTypeDLMSP" + configIndex + "MetCfg" + tablerowIndex).classList.add("disableCSS");
        }
        var elem = document.getElementById("portFAULTPwdDLMSP" + configIndex + "MetCfg" + tablerowIndex);
        if (typeof elem !== 'undefined' && elem !== null) {
          document.getElementById("portFAULTPwdDLMSP" + configIndex + "MetCfg" + tablerowIndex).disabled = true;
          document.getElementById("portFAULTPwdDLMSP" + configIndex + "MetCfg" + tablerowIndex).classList.add("disableCSS");
        }
        var elem = document.getElementById("portFAULTLocDLMSP" + configIndex + "MetCfg" + tablerowIndex);
        if (typeof elem !== 'undefined' && elem !== null) {
          document.getElementById("portFAULTLocDLMSP" + configIndex + "MetCfg" + tablerowIndex).disabled = true;
          document.getElementById("portFAULTLocDLMSP" + configIndex + "MetCfg" + tablerowIndex).classList.add("disableCSS");
        }
        var elem = document.getElementById("portFAULTTODLMSP" + configIndex + "MetCfg" + tablerowIndex);
        if (typeof elem !== 'undefined' && elem !== null) {
          document.getElementById("portFAULTTODLMSP" + configIndex + "MetCfg" + tablerowIndex).disabled = true;
          document.getElementById("portFAULTTODLMSP" + configIndex + "MetCfg" + tablerowIndex).classList.add("disableCSS");
        }
        var elem = document.getElementById("portFAULTRetCntDLMSP" + configIndex + "MetCfg" + tablerowIndex);
        if (typeof elem !== 'undefined' && elem !== null) {
          document.getElementById("portFAULTRetCntDLMSP" + configIndex + "MetCfg" + tablerowIndex).disabled = true;
          document.getElementById("portFAULTRetCntDLMSP" + configIndex + "MetCfg" + tablerowIndex).classList.add("disableCSS");
        }
      }
      this.saveMeterConfigPage();
    },
    enableEthnetMeterdevice: function enableEthnetMeterdevice(rowIndex, id) {
      var ethnetcheckboxVal = document.getElementById("ethnetcheckbox" + (rowIndex + 1)).checked;
      if (ethnetcheckboxVal) {
        var elem = document.getElementById("ethnetipaddress" + (rowIndex + 1));
        if (typeof elem !== 'undefined' && elem !== null) {
          document.getElementById("ethnetipaddress" + (rowIndex + 1)).disabled = false;
          document.getElementById("ethnetipaddress" + (rowIndex + 1)).classList.remove("disableCSS");
        }
        var elem = document.getElementById("ethnetport" + (rowIndex + 1));
        if (typeof elem !== 'undefined' && elem !== null) {
          document.getElementById("ethnetport" + (rowIndex + 1)).disabled = false;
          document.getElementById("ethnetport" + (rowIndex + 1)).classList.remove("disableCSS");
        }
        var elem = document.getElementById("ethnetPwd" + (rowIndex + 1));
        if (typeof elem !== 'undefined' && elem !== null) {
          document.getElementById("ethnetPwd" + (rowIndex + 1)).disabled = false;
          document.getElementById("ethnetPwd" + (rowIndex + 1)).classList.remove("disableCSS");
        }
        var elem = document.getElementById("ethnetLoc" + (rowIndex + 1));
        if (typeof elem !== 'undefined' && elem !== null) {
          document.getElementById("ethnetLoc" + (rowIndex + 1)).disabled = false;
          document.getElementById("ethnetLoc" + (rowIndex + 1)).classList.remove("disableCSS");
        }
        var elem = document.getElementById("ethnetTO" + (rowIndex + 1));
        if (typeof elem !== 'undefined' && elem !== null) {
          document.getElementById("ethnetTO" + (rowIndex + 1)).disabled = false;
          document.getElementById("ethnetTO" + (rowIndex + 1)).classList.remove("disableCSS");
        }
        var elem = document.getElementById("ethnetRetCnt" + (rowIndex + 1));
        if (typeof elem !== 'undefined' && elem !== null) {
          document.getElementById("ethnetRetCnt" + (rowIndex + 1)).disabled = false;
          document.getElementById("ethnetRetCnt" + (rowIndex + 1)).classList.remove("disableCSS");
        }
      } else {
        var elem = document.getElementById("ethnetipaddress" + (rowIndex + 1));
        if (typeof elem !== 'undefined' && elem !== null) {
          document.getElementById("ethnetipaddress" + (rowIndex + 1)).disabled = true;
          document.getElementById("ethnetipaddress" + (rowIndex + 1)).classList.add("disableCSS");
        }
        var elem = document.getElementById("ethnetport" + (rowIndex + 1));
        if (typeof elem !== 'undefined' && elem !== null) {
          document.getElementById("ethnetport" + (rowIndex + 1)).disabled = true;
          document.getElementById("ethnetport" + (rowIndex + 1)).classList.add("disableCSS");
        }
        var elem = document.getElementById("ethnetPwd" + (rowIndex + 1));
        if (typeof elem !== 'undefined' && elem !== null) {
          document.getElementById("ethnetPwd" + (rowIndex + 1)).disabled = true;
          document.getElementById("ethnetPwd" + (rowIndex + 1)).classList.add("disableCSS");
        }
        var elem = document.getElementById("ethnetLoc" + (rowIndex + 1));
        if (typeof elem !== 'undefined' && elem !== null) {
          document.getElementById("ethnetLoc" + (rowIndex + 1)).disabled = true;
          document.getElementById("ethnetLoc" + (rowIndex + 1)).classList.add("disableCSS");
        }
        var elem = document.getElementById("ethnetTO" + (rowIndex + 1));
        if (typeof elem !== 'undefined' && elem !== null) {
          document.getElementById("ethnetTO" + (rowIndex + 1)).disabled = true;
          document.getElementById("ethnetTO" + (rowIndex + 1)).classList.add("disableCSS");
        }
        var elem = document.getElementById("ethnetRetCnt" + (rowIndex + 1));
        if (typeof elem !== 'undefined' && elem !== null) {
          document.getElementById("ethnetRetCnt" + (rowIndex + 1)).disabled = true;
          document.getElementById("ethnetRetCnt" + (rowIndex + 1)).classList.add("disableCSS");
        }
      }
      this.saveMeterConfigPage();
    },

    isNumber: function isNumber(evt) {
      evt = evt ? true : window.event;
      var charCode = evt.which ? evt.which : evt.keyCode;
      if (charCode > 31 && (charCode < 48 || charCode > 57) && charCode !== 46) {
        evt.preventDefault();
      } else {
        return true;
      }
    },
    successMessage: function successMessage(msg) {
      this.$notice.success({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    warningMessage: function warningMessage(msg) {
      this.$notice.warning({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    infoMessage: function infoMessage(msg) {
      this.$notice.info({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    errorMessage: function errorMessage(msg) {
      this.$notice.error({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    }
  }
});

/***/ }),
/* 45 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
Object.defineProperty(__webpack_exports__, "__esModule", { value: true });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_crip_vue_notice__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_crip_vue_notice___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_0_crip_vue_notice__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_vue_element_loading__ = __webpack_require__(2);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_vue_element_loading___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_1_vue_element_loading__);




/* harmony default export */ __webpack_exports__["default"] = ({
  name: 'Changepass',
  components: {
    CripNotice: __WEBPACK_IMPORTED_MODULE_0_crip_vue_notice___default.a,
    VueElementLoading: __WEBPACK_IMPORTED_MODULE_1_vue_element_loading___default.a
  },
  data: function data() {
    return {
      isLoading: false,
      onDemandSerialNoTXT: 'Meter Serial Number',
      onDemandCommandTXT: 'Choose Command',
      onDemandTableheight: 0,
      ondemandconfigJson: { details: [{ id: 1, date: '13-08-2020', view: '', download: '' }, { id: 2, date: '12-08-2020', view: '', download: '' }, { id: 3, date: '11-08-2020', view: '', download: '' }, { id: 4, date: '10-08-2020', view: '', download: '' }, { id: 5, date: '09-08-2020', view: '', download: '' }, { id: 6, date: '08-08-2020', view: '', download: '' }, { id: 7, date: '07-08-2020', view: '', download: '' }, { id: 8, date: '06-08-2020', view: '', download: '' }, { id: 9, date: '05-08-2020', view: '', download: '' }, { id: 10, date: '04-08-2020', view: '', download: '' }, { id: 11, date: '03-08-2020', view: '', download: '' }, { id: 12, date: '02-08-2020', view: '', download: '' }, { id: 13, date: '01-08-2020', view: '', download: '' }, { id: 14, date: '30-07-2020', view: '', download: '' }] }
    };
  },
  created: function created() {
    if (this.$session.get("loginsession") == "") {
      this.$router.replace({ path: '/' });
      return false;
    }
  },
  mounted: function mounted() {
    var _this = this;

    this.isLoading = true;
    var innerMinHeight = window.innerHeight - 125 + 'px';
    this.onDemandTableheight = window.innerHeight - 350 + 'px';
    document.getElementById('onDemandPage').style.minHeight = innerMinHeight;
    setTimeout(function () {
      return _this.isLoading = false;
    }, 500);
  },

  methods: {
    viewDATA: function viewDATA() {
      var _this2 = this;

      this.isLoading = true;
      setTimeout(function () {
        return _this2.isLoading = false;
      }, 1000);
    },
    downloadDATA: function downloadDATA() {
      var _this3 = this;

      this.isLoading = true;
      setTimeout(function () {
        return _this3.isLoading = false;
      }, 1000);
    },

    isNumber: function isNumber(evt) {
      evt = evt ? true : window.event;
      var charCode = evt.which ? evt.which : evt.keyCode;
      if (charCode > 31 && (charCode < 48 || charCode > 57) && charCode !== 46) {
        evt.preventDefault();
      } else {
        return true;
      }
    },
    successMessage: function successMessage(msg) {
      this.$notice.success({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    warningMessage: function warningMessage(msg) {
      this.$notice.warning({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    infoMessage: function infoMessage(msg) {
      this.$notice.info({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    errorMessage: function errorMessage(msg) {
      this.$notice.error({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    }
  }
});

/***/ }),
/* 46 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
Object.defineProperty(__webpack_exports__, "__esModule", { value: true });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_crip_vue_notice__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_crip_vue_notice___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_0_crip_vue_notice__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_vue_element_loading__ = __webpack_require__(2);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_vue_element_loading___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_1_vue_element_loading__);




/* harmony default export */ __webpack_exports__["default"] = ({
  name: 'ParamsConfig',
  components: {
    CripNotice: __WEBPACK_IMPORTED_MODULE_0_crip_vue_notice___default.a,
    VueElementLoading: __WEBPACK_IMPORTED_MODULE_1_vue_element_loading___default.a
  },
  data: function data() {
    return {
      masterINSTConfigJSON: this.$session.get("get_MasterINSTJSON"),
      masterLSConfigJSON: this.$session.get("get_MasterLSJSON"),
      masterMNConfigJSON: this.$session.get("get_MasterMNJSON"),
      masterEVENTConfigJSON: this.$session.get("get_MasterEVENTJSON"),
      masterBillConfigJSON: this.$session.get("get_MasterBILLJSON"),
      selectedINSTConfigJSON: this.$session.get("get_SelectedINSTJSON"),
      selectedLSConfigJSON: this.$session.get("get_SelectedLSJSON"),
      selectedMNConfigJSON: this.$session.get("get_SelectedMNJSON"),
      selectedEVENTConfigJSON: this.$session.get("get_SelectedEVENTJSON"),
      selectedBillConfigJSON: this.$session.get("get_SelectedBILLJSON"),
      paramsSELECTEDConfigJSON: this.$session.get("ParamselectedJSON"),
      isLoading: false,
      instanListheight: 0,
      instanMasterParamsList: [],
      instanselectedParamsList: [],
      loadserveListheight: 0,
      loadserveMasterParamsList: [],
      loadserveselectedParamsList: [],
      eventdataListheight: 0,
      eventdataMasterParamsList: [],
      eventdataselectedParamsList: [],
      midnightListheight: 0,
      midnightMasterParamsList: [],
      midnightselectedParamsList: [],
      billingListheight: 0,
      billingMasterParamsList: [],
      billingselectedParamsList: []
    };
  },
  created: function created() {
    if (this.$session.get("loginsession") == "") {
      this.$router.replace({ path: '/' });
      return false;
    }
    this.instanMasterParamsList = this.masterINSTConfigJSON.DATA.InstParams.ObisCodeList;
    this.loadserveMasterParamsList = this.masterLSConfigJSON.DATA.LSParams.ObisCodeList;
    this.eventdataMasterParamsList = this.masterEVENTConfigJSON.DATA.EventParams.ObisCodeList;
    this.midnightMasterParamsList = this.masterMNConfigJSON.DATA.MNParams.ObisCodeList;
    this.billingMasterParamsList = this.masterBillConfigJSON.DATA.BillParams.ObisCodeList;
    this.instanselectedParamsList = this.selectedINSTConfigJSON.DATA.InstParams.ObisCodeList;
    this.loadserveselectedParamsList = this.selectedLSConfigJSON.DATA.LSParams.ObisCodeList;
    this.midnightselectedParamsList = this.selectedMNConfigJSON.DATA.MNParams.ObisCodeList;
    this.eventdataselectedParamsList = this.selectedEVENTConfigJSON.DATA.EventParams.ObisCodeList;
    this.billingselectedParamsList = this.selectedBillConfigJSON.DATA.BillParams.ObisCodeList;
  },
  mounted: function mounted() {
    var _this = this;

    this.isLoading = true;
    var innerMinHeight = window.innerHeight - 150 + 'px';
    this.instanListheight = window.innerHeight - 320 + 'px';
    document.getElementById('paramsconfigpane').style.minHeight = innerMinHeight;
    setTimeout(function () {
      return _this.isLoading = false;
    }, 500);
    this.loadINSTcheckbox();
    this.loadLScheckbox();
    this.loadMNcheckbox();
    this.loadEVENTcheckbox();
    this.loadBILLcheckbox();
  },
  updated: function updated() {
    this.selectedINSTConfigJSON.DATA.InstParams.NumParams = this.instanselectedParamsList.length.toString();
    this.selectedINSTConfigJSON.DATA.InstParams.ObisCodeList = this.instanselectedParamsList;
    this.selectedLSConfigJSON.DATA.LSParams.NumParams = this.loadserveselectedParamsList.length.toString();
    this.selectedLSConfigJSON.DATA.LSParams.ObisCodeList = this.loadserveselectedParamsList;
    this.selectedMNConfigJSON.DATA.MNParams.NumParams = this.midnightselectedParamsList.length.toString();
    this.selectedMNConfigJSON.DATA.MNParams.ObisCodeList = this.midnightselectedParamsList;
    this.selectedEVENTConfigJSON.DATA.EventParams.NumParams = this.eventdataselectedParamsList.length.toString();
    this.selectedEVENTConfigJSON.DATA.EventParams.ObisCodeList = this.eventdataselectedParamsList;
    this.selectedBillConfigJSON.DATA.BillParams.NumParams = this.billingselectedParamsList.length.toString();
    this.selectedBillConfigJSON.DATA.BillParams.ObisCodeList = this.billingselectedParamsList;
    this.$session.set("get_SelectedINSTJSON", this.selectedINSTConfigJSON);
    this.$session.set("get_SelectedLSJSON", this.selectedLSConfigJSON);
    this.$session.set("get_SelectedMNJSON", this.selectedMNConfigJSON);
    this.$session.set("get_SelectedEVENTJSON", this.selectedEVENTConfigJSON);
    this.$session.set("get_SelectedBILLJSON", this.selectedBillConfigJSON);
  },
  beforeCreate: function beforeCreate() {},

  methods: {
    getINSTassignName: function getINSTassignName(rowIndex, id) {
      var newassignVal = document.getElementById(id).value;
      this.instanselectedParamsList[rowIndex].assign = newassignVal;
    },
    getLSassignName: function getLSassignName(rowIndex, id) {
      var newassignVal = document.getElementById(id).value;
      this.loadserveselectedParamsList[rowIndex].assign = newassignVal;
    },
    getMNassignName: function getMNassignName(rowIndex, id) {
      var newassignVal = document.getElementById(id).value;
      this.midnightselectedParamsList[rowIndex].assign = newassignVal;
    },
    getEVENTassignName: function getEVENTassignName(rowIndex, id) {
      var newassignVal = document.getElementById(id).value;
      this.eventdataselectedParamsList[rowIndex].assign = newassignVal;
    },
    getBILLassignName: function getBILLassignName(rowIndex, id) {
      var newassignVal = document.getElementById(id).value;
      this.billingselectedParamsList[rowIndex].assign = newassignVal;
    },
    parameterconfigPageValidation: function parameterconfigPageValidation() {
      if (this.instanselectedParamsList.length != 0) {
        for (var jj = 0; jj < this.instanselectedParamsList.length; jj++) {
          if (document.getElementById('instTXT' + (jj + 1)).value == "") {
            this.warningMessage("Please enter a seleced instantaneous assign value");
            this.$router.replace({ path: '/dcu/paramsconfig' });
            return false;
          }
        }
      }
      if (this.loadserveselectedParamsList.length != 0) {
        for (var jk = 0; jk < this.loadserveselectedParamsList.length; jk++) {
          if (document.getElementById('loadsvyTXT' + (jk + 1)).value == "") {
            this.warningMessage("Please enter a seleced load survey assign value");
            this.$router.replace({ path: '/dcu/paramsconfig' });
            return false;
          }
        }
      }
      if (this.eventdataselectedParamsList.length != 0) {
        for (var jm = 0; jm < this.eventdataselectedParamsList.length; jm++) {
          if (document.getElementById('eventdataTXT' + (jm + 1)).value == "") {
            this.warningMessage("Please enter a seleced event data assign value");
            this.$router.replace({ path: '/dcu/paramsconfig' });
            return false;
          }
        }
      }
      if (this.midnightselectedParamsList.length != 0) {
        for (var jt = 0; jt < this.midnightselectedParamsList.length; jt++) {
          if (document.getElementById('midnightselTXT' + (jt + 1)).value == "") {
            this.warningMessage("Please enter a seleced mid night assign value");
            this.$router.replace({ path: '/dcu/paramsconfig' });
            return false;
          }
        }
      }
      if (this.billingselectedParamsList.length != 0) {
        for (var jp = 0; jp < this.billingselectedParamsList.length; jp++) {
          if (document.getElementById('bilselTXT' + (jp + 1)).value == "") {
            this.warningMessage("Please enter a seleced billing assign value");
            this.$router.replace({ path: '/dcu/paramsconfig' });
            return false;
          }
        }
      }
    },
    loadINSTcheckbox: function loadINSTcheckbox() {
      for (var instindex = 0; instindex < this.instanMasterParamsList.length; instindex++) {
        for (var selindex = 0; selindex < this.instanselectedParamsList.length; selindex++) {
          if (this.instanMasterParamsList[instindex].obis == this.instanselectedParamsList[selindex].obis) {
            document.getElementById('masterINSTCheckbox' + (instindex + 1)).checked = true;
          }
        }
      }
    },
    checkedmasterINSTfunction: function checkedmasterINSTfunction(id, instObject) {
      var check = document.getElementById(id).checked;
      var obisname = instObject.obis;
      if (check) {
        instObject["assign"] = instObject.def;
        this.instanselectedParamsList.push(instObject);
      } else {
        this.instanselectedParamsList.splice(this.instanselectedParamsList.findIndex(function (e) {
          return e.obis === obisname;
        }), 1);
      }
    },
    loadLScheckbox: function loadLScheckbox() {
      for (var lsindex = 0; lsindex < this.loadserveMasterParamsList.length; lsindex++) {
        for (var selindex = 0; selindex < this.loadserveselectedParamsList.length; selindex++) {
          if (this.loadserveMasterParamsList[lsindex].obis == this.loadserveselectedParamsList[selindex].obis) {
            document.getElementById('masterLSCheckbox' + (lsindex + 1)).checked = true;
          }
        }
      }
    },
    checkedmasterLSfunction: function checkedmasterLSfunction(id, lsObject) {
      var check = document.getElementById(id).checked;
      var obisname = lsObject.obis;
      if (check) {
        lsObject["assign"] = lsObject.def;
        this.loadserveMasterParamsList.push(lsObject);
      } else {
        this.loadserveMasterParamsList.splice(this.loadserveMasterParamsList.findIndex(function (e) {
          return e.obis === obisname;
        }), 1);
      }
    },
    loadMNcheckbox: function loadMNcheckbox() {
      for (var mnindex = 0; mnindex < this.midnightMasterParamsList.length; mnindex++) {
        for (var selindex = 0; selindex < this.midnightselectedParamsList.length; selindex++) {
          if (this.midnightMasterParamsList[mnindex].obis == this.midnightselectedParamsList[selindex].obis) {
            document.getElementById('masterMNCheckbox' + (mnindex + 1)).checked = true;
          }
        }
      }
    },
    checkedmasterMNfunction: function checkedmasterMNfunction(id, mnObject) {
      var check = document.getElementById(id).checked;
      var obisname = mnObject.obis;
      if (check) {
        mnObject["assign"] = mnObject.def;
        this.midnightselectedParamsList.push(mnObject);
      } else {
        this.midnightselectedParamsList.splice(this.midnightselectedParamsList.findIndex(function (e) {
          return e.obis === obisname;
        }), 1);
      }
    },
    loadEVENTcheckbox: function loadEVENTcheckbox() {
      for (var eventindex = 0; eventindex < this.eventdataMasterParamsList.length; eventindex++) {
        for (var selindex = 0; selindex < this.eventdataselectedParamsList.length; selindex++) {
          if (this.eventdataMasterParamsList[eventindex].obis == this.eventdataselectedParamsList[selindex].obis) {
            document.getElementById('masterEVENTCheckbox' + (eventindex + 1)).checked = true;
          }
        }
      }
    },
    checkedmasterEVENTfunction: function checkedmasterEVENTfunction(id, eventObject) {
      var check = document.getElementById(id).checked;
      var obisname = eventObject.obis;
      if (check) {
        eventObject["assign"] = eventObject.def;
        this.eventdataselectedParamsList.push(eventObject);
      } else {
        this.eventdataselectedParamsList.splice(this.eventdataselectedParamsList.findIndex(function (e) {
          return e.obis === obisname;
        }), 1);
      }
    },
    loadBILLcheckbox: function loadBILLcheckbox() {
      for (var billindex = 0; billindex < this.billingMasterParamsList.length; billindex++) {
        for (var selindex = 0; selindex < this.billingselectedParamsList.length; selindex++) {
          if (this.billingMasterParamsList[billindex].obis == this.billingselectedParamsList[selindex].obis) {
            document.getElementById('masterBILLCheckbox' + (billindex + 1)).checked = true;
          }
        }
      }
    },
    checkedmasterBILLfunction: function checkedmasterBILLfunction(id, billObject) {
      var check = document.getElementById(id).checked;
      var obisname = billObject.obis;
      if (check) {
        billObject["assign"] = billObject.def;
        this.billingselectedParamsList.push(billObject);
      } else {
        this.billingselectedParamsList.splice(this.billingselectedParamsList.findIndex(function (e) {
          return e.obis === obisname;
        }), 1);
      }
    },

    isNumber: function isNumber(evt) {
      evt = evt ? true : window.event;
      var charCode = evt.which ? evt.which : evt.keyCode;
      if (charCode > 31 && (charCode < 48 || charCode > 57) && charCode !== 46) {
        evt.preventDefault();
      } else {
        return true;
      }
    },
    successMessage: function successMessage(msg) {
      this.$notice.success({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    warningMessage: function warningMessage(msg) {
      this.$notice.warning({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    infoMessage: function infoMessage(msg) {
      this.$notice.info({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    errorMessage: function errorMessage(msg) {
      this.$notice.error({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    }
  }
});

/***/ }),
/* 47 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
Object.defineProperty(__webpack_exports__, "__esModule", { value: true });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify__ = __webpack_require__(3);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_crip_vue_notice__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_crip_vue_notice___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_1_crip_vue_notice__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2_vue_element_loading__ = __webpack_require__(2);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2_vue_element_loading___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_2_vue_element_loading__);





/* harmony default export */ __webpack_exports__["default"] = ({
  name: 'SaveRestart',
  components: {
    CripNotice: __WEBPACK_IMPORTED_MODULE_1_crip_vue_notice___default.a,
    VueElementLoading: __WEBPACK_IMPORTED_MODULE_2_vue_element_loading___default.a
  },
  data: function data() {
    return {
      saveDeviceCONFIGpageJSON: this.$session.get('get_GenconfigJSON'),
      saveUppstreamCONFIGpageJSON: this.$session.get('get_UpstreamconfigJSON'),
      saveMeterCONFIGpageJSON: this.$session.get('get_DlmsMeterconfigSON'),
      saveParamsINSTelectedJSON: this.$session.get('get_SelectedINSTJSON'),
      saveParamsLSelectedJSON: this.$session.get('get_SelectedLSJSON'),
      saveParamsMNCONFIGpageJSON: this.$session.get('get_SelectedMNJSON'),
      saveParamsEVENTCONFIGpageJSON: this.$session.get('get_SelectedEVENTJSON'),
      saveParamsBILLCONFIGpageJSON: this.$session.get('get_SelectedBILLJSON'),
      copy_saveDeviceCONFIGpageJSON: this.$session.get('get_copy_GenconfigJSON'),
      copy_saveUppstreamCONFIGpageJSON: this.$session.get('get_copy_UpstreamconfigJSON'),
      copy_saveMeterCONFIGpageJSON: this.$session.get('get_copy_DlmsMeterconfigSON'),
      copy_saveParamsINSTelectedJSON: this.$session.get('get_copy_SelectedINSTJSON'),
      copy_saveParamsLSelectedJSON: this.$session.get('get_copy_SelectedLSJSON'),
      copy_saveParamsMNCONFIGpageJSON: this.$session.get('get_copy_SelectedMNJSON'),
      copy_saveParamsEVENTCONFIGpageJSON: this.$session.get('get_copy_SelectedEVENTJSON'),
      copy_saveParamsBILLCONFIGpageJSON: this.$session.get('get_copy_SelectedBILLJSON'),
      blockdevice: false,
      isRunning: false,
      interval: null,
      msg: '',
      html: '',
      isLoading: false,
      saveEthcount: '1',
      saveDCUIdTXT: '',
      saveDCULocTXT: '',
      saveDCUserialNumTXT: '',
      saveDCUEnableDbgLogTXT: '',
      saveDCUDbgLogLevelTXT: '',
      saveDCUDbgLogIpTXT: '',
      saveEth1currIPTXT: '',
      saveEth1newIPTXT: '',
      saveEth1subnetIPTXT: '',
      saveEth1gatewayIPTXT: '',
      saveEth2currIPTXT: '',
      saveEth2newIPTXT: '',
      saveEth2subnetIPTXT: '',
      saveEth2gatewayIPTXT: '',
      saveModemEnableTXT: '',
      saveModemUsernameTXT: '',
      saveModemPasswordTXT: '',
      saveModemPhnumTXT: '*',
      saveModemAPNTXT: '',
      saveModemEnablePingTXT: '',
      saveModemNoPingTXT: '',
      saveModemPingIntervalTXT: '',
      saveModemPingIpaddressTXT: '',
      smsEnableTXT: '',
      saveNTPserver1EnableTXT: '',
      saveNTPserver1IPaddressTXT: '',
      saveNTPserver1PortTXT: '',
      saveNTPserver2EnableTXT: '',
      saveNTPserver2IPaddressTXT: '',
      saveNTPserver2PortTXT: '',
      saveNTPserverIntervalTXT: '',
      saveICEEnableTXT: '',
      saveICEstationAddTXT: '',
      saveICEstartIOAAddTXT: '',
      saveICEcyclicTXT: '',
      saveICEcotTXT: '',
      saveICEportTXT: '',
      saveICEiotTXT: '',
      saveAllowedEnableCheckboxTXT: '',
      saveAllowed1statusTXT: '',
      saveAllowed1IPTXT: '',
      saveAllowed2statusTXT: '',
      saveAllowed2IPTXT: '',
      saveAllowed3statusTXT: '',
      saveAllowed3IPTXT: '',
      saveAllowed4statusTXT: '',
      saveAllowed4IPTXT: '',
      saveFTPEnableTXT: '',
      saveFTPipAddTXT: '',
      saveFTPportnoAddTXT: '',
      saveFTPusernameTXT: '',
      saveFTPpasswordTXT: '',
      saveFTPdirTXT: '',
      saveFTPtimeintervalTXT: '',
      saveFTPLOGEnableTXT: '',
      saveFTPLOGipAddTXT: '',
      saveFTPLOGportnoAddTXT: '',
      saveFTPLOGusernameTXT: '',
      saveFTPLOGpasswordTXT: '',
      saveFTPLOGdirTXT: '',
      saveFTPLOGtimeintervalTXT: '',
      saveTCPEnableTXT: '',
      saveTCPdeviceIdTXT: '',
      saveTCPRespToAllSlaveIdTXT: '',
      saveTCPPortTXT: '',
      saveTCPholdstartAddTXT: '',
      saveTCPinputstartAddTXT: '',
      saveTCPDiscriteinputstartAddTXT: '',
      saveMQTTEnableTXT: '',
      saveMQTTBrokerIpTXT: '',
      saveMQTTPortnoTXT: '',
      saveMQTTUserTXT: '',
      saveMQTTPassTXT: '',
      saveMQTTcyclicDataTXT: '',
      saveMQTTcmdtopicTXT: '',
      saveMQTTenabletopicTXT: '',
      saveMQTTeventtopicTXT: '',
      saveMQTTenableDiagTXT: '',
      saveMQTTDiagTopicTXT: '',
      saveMQTTCyclicPeriodTXT: '',
      saveCMSEMSEnableTXT: '',
      saveCMSEMSipTXT: '',
      saveCMSEMSportnoTXT: '',
      saveCMSEMSeventenableTXT: '',
      saveCMSEMSdiagenableTXT: '',
      saveCMSEMScyclicperoidenableTXT: '',
      saveETHNETInstantaneousTXT: '',
      saveETHNETLoadServeTXT: '',
      saveETHNETeventDataTXT: '',
      saveETHNETmidnightTXT: '',
      saveETHNETbillingtTXT: '',
      saveSERIALInstantaneousTXT: '',
      saveSERIALLoadServeTXT: '',
      saveSERIALEventDataTXT: '',
      saveSERIALMidnightTXT: '',
      saveSERIALBillingTXT: '',
      saveSERIALMidnightPeriodTXT: '',
      saveSERIALBillingPeriodTXT: '',
      saveFAULTInstantaneousTXT: '',
      saveFAULTLoadServeTXT: '',
      saveFAULTEventDataTXT: '',
      saveFAULTMidnightTXT: '',
      saveFAULTBillingTXT: '',
      saveFAULTMidnightPeriodTXT: '',
      saveFAULTBillingPeriodTXT: '',
      saveinstselectedParamsList: [],
      saveloadserveselectedParamsList: [],
      saveeventselectedParamsList: [],
      savemidnightselectedParamsList: [],
      savebillingselectedParamsList: [],
      durationlimit: 60000,
      time: 60,
      clicksave: false
    };
  },
  mounted: function mounted() {
    var _this = this;

    this.isLoading = true;
    var innerMinHeight = window.innerHeight - 125 + 'px';
    document.getElementById('saveRestartPane').style.minHeight = innerMinHeight;
    this.loadsavedetails();
    setTimeout(function () {
      return _this.isLoading = false;
    }, 500);
  },
  created: function created() {
    if (this.$session.get("loginsession") == "") {
      this.$router.replace({ path: '/' });
      return false;
    }
  },
  destroyed: function destroyed() {
    clearInterval(this.interval);
    if (this.clicksave) {
      this.ws.close();
    }
  },

  methods: {
    loadsavedetails: function loadsavedetails() {
      this.saveDCUIdTXT = this.saveDeviceCONFIGpageJSON.DATA.GenCfg.DcuID;
      this.saveDCULocTXT = this.saveDeviceCONFIGpageJSON.DATA.GenCfg.Location;
      this.saveDCUserialNumTXT = this.saveDeviceCONFIGpageJSON.DATA.GenCfg.SerNum;
      this.saveDCUEnableDbgLogTXT = this.saveDeviceCONFIGpageJSON.DATA.GenCfg.EnableDbgLog;
      if (this.saveDeviceCONFIGpageJSON.DATA.GenCfg.DbgLogLevel == "1") {
        this.saveDCUDbgLogLevelTXT = "All";
      } else if (this.saveDeviceCONFIGpageJSON.DATA.GenCfg.DbgLogLevel == "2") {
        this.saveDCUDbgLogLevelTXT = "Critical";
      } else if (this.saveDeviceCONFIGpageJSON.DATA.GenCfg.DbgLogLevel == "3") {
        this.saveDCUDbgLogLevelTXT = "Alarms";
      } else if (this.saveDeviceCONFIGpageJSON.DATA.GenCfg.DbgLogLevel == "4") {
        this.saveDCUDbgLogLevelTXT = "Warnings";
      }

      this.saveDCUDbgLogIpTXT = this.saveDeviceCONFIGpageJSON.DATA.GenCfg.DbgLogIp;
      this.saveEthcount = this.saveDeviceCONFIGpageJSON.DATA.EthCfg.NumEthPorts;
      this.saveEth1currIPTXT = this.saveDeviceCONFIGpageJSON.DATA.EthCfg.EthCfg[0].CurrIp;
      this.saveEth1newIPTXT = this.saveDeviceCONFIGpageJSON.DATA.EthCfg.EthCfg[0].NewIp;
      this.saveEth1subnetIPTXT = this.saveDeviceCONFIGpageJSON.DATA.EthCfg.EthCfg[0].NetMask;
      this.saveEth1gatewayIPTXT = this.saveDeviceCONFIGpageJSON.DATA.EthCfg.EthCfg[0].GW;
      if (this.saveDeviceCONFIGpageJSON.DATA.EthCfg.NumEthPorts == '2') {
        this.saveEth2currIPTXT = this.saveDeviceCONFIGpageJSON.DATA.EthCfg.EthCfg[1].CurrIp;
        this.saveEth2newIPTXT = this.saveDeviceCONFIGpageJSON.DATA.EthCfg.EthCfg[1].NewIp;
        this.saveEth2subnetIPTXT = this.saveDeviceCONFIGpageJSON.DATA.EthCfg.EthCfg[1].NetMask;
        this.saveEth2gatewayIPTXT = this.saveDeviceCONFIGpageJSON.DATA.EthCfg.EthCfg[1].GW;
      }
      this.saveModemEnableTXT = this.saveDeviceCONFIGpageJSON.DATA.ModemCfg.EnableModem;
      this.saveModemUsernameTXT = this.saveDeviceCONFIGpageJSON.DATA.ModemCfg.Username;
      this.saveModemPasswordTXT = this.saveDeviceCONFIGpageJSON.DATA.ModemCfg.Password;
      this.saveModemPhnumTXT = this.saveDeviceCONFIGpageJSON.DATA.ModemCfg.PhoneNum;
      this.saveModemAPNTXT = this.saveDeviceCONFIGpageJSON.DATA.ModemCfg.AccessPtName;
      this.saveModemEnablePingTXT = this.saveDeviceCONFIGpageJSON.DATA.ModemCfg.EnablePing;
      this.saveModemNoPingTXT = this.saveDeviceCONFIGpageJSON.DATA.ModemCfg.NumPings;
      this.saveModemPingIntervalTXT = this.saveDeviceCONFIGpageJSON.DATA.ModemCfg.PingInt;
      this.saveModemPingIpaddressTXT = this.saveDeviceCONFIGpageJSON.DATA.ModemCfg.IpAddr;
      this.saveNTPserver1EnableTXT = this.saveDeviceCONFIGpageJSON.DATA.NtpCfg.EnableNtp1;
      this.saveNTPserver1IPaddressTXT = this.saveDeviceCONFIGpageJSON.DATA.NtpCfg.NtpIpAddr1;
      this.saveNTPserver1PortTXT = this.saveDeviceCONFIGpageJSON.DATA.NtpCfg.NtpPort1;
      this.saveNTPserver2EnableTXT = this.saveDeviceCONFIGpageJSON.DATA.NtpCfg.EnableNtp2;
      this.saveNTPserver2IPaddressTXT = this.saveDeviceCONFIGpageJSON.DATA.NtpCfg.NtpIpAddr2;
      this.saveNTPserver2PortTXT = this.saveDeviceCONFIGpageJSON.DATA.NtpCfg.NtpPort2;
      this.saveNTPserverIntervalTXT = this.saveDeviceCONFIGpageJSON.DATA.NtpCfg.Interval;

      this.smsEnableTXT = this.saveUppstreamCONFIGpageJSON.DATA.UpstreamDataCfg.SMSSupp;

      this.saveICEEnableTXT = this.saveUppstreamCONFIGpageJSON.DATA.UpstreamDataCfg.IEC104Supp;
      this.saveICEstationAddTXT = this.saveUppstreamCONFIGpageJSON.DATA.IEC104Cfg.StationAddr;
      this.saveICEstartIOAAddTXT = this.saveUppstreamCONFIGpageJSON.DATA.IEC104Cfg.MetStartIoa;
      this.saveICEcyclicTXT = this.saveUppstreamCONFIGpageJSON.DATA.IEC104Cfg.CycInt;
      this.saveICEcotTXT = this.saveUppstreamCONFIGpageJSON.DATA.IEC104Cfg.CotSize;
      this.saveICEportTXT = this.saveUppstreamCONFIGpageJSON.DATA.IEC104Cfg.PortNo;
      this.saveICEiotTXT = this.saveUppstreamCONFIGpageJSON.DATA.IEC104Cfg.IoaSize;
      this.saveAllowedEnableCheckboxTXT = this.saveDeviceCONFIGpageJSON.DATA.AllowedMasterCfg.EnableAllowMaster;
      this.saveAllowed1statusTXT = this.saveDeviceCONFIGpageJSON.DATA.AllowedMasterCfg.AllowedMasterList[0].Enable;
      this.saveAllowed1IPTXT = this.saveDeviceCONFIGpageJSON.DATA.AllowedMasterCfg.AllowedMasterList[0].Ip;
      this.saveAllowed2statusTXT = this.saveDeviceCONFIGpageJSON.DATA.AllowedMasterCfg.AllowedMasterList[1].Enable;
      this.saveAllowed2IPTXT = this.saveDeviceCONFIGpageJSON.DATA.AllowedMasterCfg.AllowedMasterList[1].Ip;
      this.saveAllowed3statusTXT = this.saveDeviceCONFIGpageJSON.DATA.AllowedMasterCfg.AllowedMasterList[2].Enable;
      this.saveAllowed3IPTXT = this.saveDeviceCONFIGpageJSON.DATA.AllowedMasterCfg.AllowedMasterList[2].Ip;
      this.saveAllowed4statusTXT = this.saveDeviceCONFIGpageJSON.DATA.AllowedMasterCfg.AllowedMasterList[3].Enable;
      this.saveAllowed4IPTXT = this.saveDeviceCONFIGpageJSON.DATA.AllowedMasterCfg.AllowedMasterList[3].Ip;
      this.saveFTPEnableTXT = this.saveUppstreamCONFIGpageJSON.DATA.UpstreamDataCfg.FtpPushSupp;
      this.saveFTPipAddTXT = this.saveUppstreamCONFIGpageJSON.DATA.FtpServerCfg.ServerIp;
      this.saveFTPportnoAddTXT = this.saveUppstreamCONFIGpageJSON.DATA.FtpServerCfg.PortNo;
      this.saveFTPusernameTXT = this.saveUppstreamCONFIGpageJSON.DATA.FtpServerCfg.UserName;
      this.saveFTPpasswordTXT = this.saveUppstreamCONFIGpageJSON.DATA.FtpServerCfg.Password;
      this.saveFTPdirTXT = this.saveUppstreamCONFIGpageJSON.DATA.FtpServerCfg.RemoteDir;
      this.saveFTPtimeintervalTXT = this.saveUppstreamCONFIGpageJSON.DATA.FtpServerCfg.UploadPeriod;
      this.saveFTPLOGEnableTXT = this.saveUppstreamCONFIGpageJSON.DATA.FtpServerCfg.DiffServerForLogs;
      this.saveFTPLOGipAddTXT = this.saveUppstreamCONFIGpageJSON.DATA.FtpServerCfg.LogServerIp;
      this.saveFTPLOGportnoAddTXT = this.saveUppstreamCONFIGpageJSON.DATA.FtpServerCfg.LogPortNo;
      this.saveFTPLOGusernameTXT = this.saveUppstreamCONFIGpageJSON.DATA.FtpServerCfg.LogUserName;
      this.saveFTPLOGpasswordTXT = this.saveUppstreamCONFIGpageJSON.DATA.FtpServerCfg.LogPassword;
      this.saveFTPLOGdirTXT = this.saveUppstreamCONFIGpageJSON.DATA.FtpServerCfg.LogRemoteDir;
      this.saveFTPLOGtimeintervalTXT = this.saveUppstreamCONFIGpageJSON.DATA.FtpServerCfg.LogUploadPeriod;

      this.saveTCPEnableTXT = this.saveUppstreamCONFIGpageJSON.DATA.UpstreamDataCfg.ModTcpSupp;
      this.saveTCPdeviceIdTXT = this.saveUppstreamCONFIGpageJSON.DATA.ModTcpCfg.ModDevId;
      this.saveTCPRespToAllSlaveIdTXT = this.saveUppstreamCONFIGpageJSON.DATA.ModTcpCfg.RespToAllSlaveId;
      this.saveTCPPortTXT = this.saveUppstreamCONFIGpageJSON.DATA.ModTcpCfg.PortNo;
      this.saveTCPholdstartAddTXT = this.saveUppstreamCONFIGpageJSON.DATA.ModTcpCfg.HoldRegStartAddr;
      this.saveTCPinputstartAddTXT = this.saveUppstreamCONFIGpageJSON.DATA.ModTcpCfg.InputRegStartAddr;
      this.saveTCPDiscriteinputstartAddTXT = this.saveUppstreamCONFIGpageJSON.DATA.ModTcpCfg.ReadDiscriteInputStartAddr;

      this.saveMQTTEnableTXT = this.saveUppstreamCONFIGpageJSON.DATA.UpstreamDataCfg.MQTTSupp;
      this.saveMQTTBrokerIpTXT = this.saveUppstreamCONFIGpageJSON.DATA.MQTTCfg.BrokerIp;
      this.saveMQTTPortnoTXT = this.saveUppstreamCONFIGpageJSON.DATA.MQTTCfg.PortNo;
      this.saveMQTTUserTXT = this.saveUppstreamCONFIGpageJSON.DATA.MQTTCfg.UserName;
      this.saveMQTTPassTXT = this.saveUppstreamCONFIGpageJSON.DATA.MQTTCfg.Password;
      this.saveMQTTcyclicDataTXT = this.saveUppstreamCONFIGpageJSON.DATA.MQTTCfg.CycDataTopic;
      this.saveMQTTcmdtopicTXT = this.saveUppstreamCONFIGpageJSON.DATA.MQTTCfg.CmdTopic;
      this.saveMQTTenabletopicTXT = this.saveUppstreamCONFIGpageJSON.DATA.MQTTCfg.EnableEventTopic;
      this.saveMQTTeventtopicTXT = this.saveUppstreamCONFIGpageJSON.DATA.MQTTCfg.EventTopic;
      this.saveMQTTenableDiagTXT = this.saveUppstreamCONFIGpageJSON.DATA.MQTTCfg.EnableDiagTopic;
      this.saveMQTTDiagTopicTXT = this.saveUppstreamCONFIGpageJSON.DATA.MQTTCfg.DiagTopic;
      this.saveMQTTCyclicPeriodTXT = this.saveUppstreamCONFIGpageJSON.DATA.MQTTCfg.CycPeriod;

      this.saveCMSEMSEnableTXT = this.saveUppstreamCONFIGpageJSON.DATA.UpstreamDataCfg.CMSEMSSupp;
      this.saveCMSEMSipTXT = this.saveUppstreamCONFIGpageJSON.DATA.CMSEMSCfg.BrokerIp;
      this.saveCMSEMSportnoTXT = this.saveUppstreamCONFIGpageJSON.DATA.CMSEMSCfg.PortNo;
      this.saveCMSEMSeventenableTXT = this.saveUppstreamCONFIGpageJSON.DATA.CMSEMSCfg.EnableEvent;
      this.saveCMSEMSdiagenableTXT = this.saveUppstreamCONFIGpageJSON.DATA.CMSEMSCfg.EnableDiag;
      this.saveCMSEMScyclicperoidenableTXT = this.saveUppstreamCONFIGpageJSON.DATA.CMSEMSCfg.CycPeriod;

      if (this.saveMeterCONFIGpageJSON.DATA.DLMSCfg.MeterType == "Ethernet") {
        this.saveETHNETInstantaneousTXT = this.saveMeterCONFIGpageJSON.DATA.DLMSCfg.EnableInstData;
        this.saveETHNETLoadServeTXT = this.saveMeterCONFIGpageJSON.DATA.DLMSCfg.EnableLSData;
        this.saveETHNETeventDataTXT = this.saveMeterCONFIGpageJSON.DATA.DLMSCfg.EnableEventData;
        this.saveETHNETmidnightTXT = this.saveMeterCONFIGpageJSON.DATA.DLMSCfg.EnableMidnightData;
        this.saveETHNETbillingtTXT = this.saveMeterCONFIGpageJSON.DATA.DLMSCfg.EnableBillingData;
      } else if (this.saveMeterCONFIGpageJSON.DATA.DLMSCfg.MeterType == "Serial" && this.saveMeterCONFIGpageJSON.DATA.DLMSCfg.FaultTolSupp == "No") {
        this.saveSERIALInstantaneousTXT = this.saveMeterCONFIGpageJSON.DATA.DLMSCfg.EnableInstData;
        this.saveSERIALLoadServeTXT = this.saveMeterCONFIGpageJSON.DATA.DLMSCfg.EnableLSData;
        this.saveSERIALEventDataTXT = this.saveMeterCONFIGpageJSON.DATA.DLMSCfg.EnableEventData;
        this.saveSERIALMidnightTXT = this.saveMeterCONFIGpageJSON.DATA.DLMSCfg.EnableMidnightData;
        this.saveSERIALBillingTXT = this.saveMeterCONFIGpageJSON.DATA.DLMSCfg.EnableBillingData;
        this.saveSERIALMidnightPeriodTXT = this.saveMeterCONFIGpageJSON.DATA.DLMSCfg.MidnightPollPer;
        this.saveSERIALBillingPeriodTXT = this.saveMeterCONFIGpageJSON.DATA.DLMSCfg.BillingPollPer;
        for (var portindex = 0; portindex < parseInt(this.saveDeviceCONFIGpageJSON.DATA.SerPortCfg.NumSerPorts); portindex++) {
          document.getElementById('saveSERIALCommModetTXT' + (portindex + 1)).innerHTML = this.saveDeviceCONFIGpageJSON.DATA.SerPortCfg.PortCfg[portindex].InfMode;

          document.getElementById('saveSERIALbaudrateTXT' + (portindex + 1)).innerHTML = this.saveDeviceCONFIGpageJSON.DATA.SerPortCfg.PortCfg[portindex].BaudRate;
          document.getElementById('saveSERIALstopbitsTXT' + (portindex + 1)).innerHTML = this.saveDeviceCONFIGpageJSON.DATA.SerPortCfg.PortCfg[portindex].Stopbits;
          document.getElementById('saveSERIALparityTXT' + (portindex + 1)).innerHTML = this.saveDeviceCONFIGpageJSON.DATA.SerPortCfg.PortCfg[portindex].Parity;
          document.getElementById('saveSERIALdataTXT' + (portindex + 1)).innerHTML = this.saveDeviceCONFIGpageJSON.DATA.SerPortCfg.PortCfg[portindex].Databits;
        }
      } else if (this.saveMeterCONFIGpageJSON.DATA.DLMSCfg.MeterType == "Serial" && this.saveMeterCONFIGpageJSON.DATA.DLMSCfg.FaultTolSupp == "Yes") {
        this.saveFAULTInstantaneousTXT = this.saveMeterCONFIGpageJSON.DATA.DLMSCfg.EnableInstData;
        this.saveFAULTLoadServeTXT = this.saveMeterCONFIGpageJSON.DATA.DLMSCfg.EnableLSData;
        this.saveFAULTEventDataTXT = this.saveMeterCONFIGpageJSON.DATA.DLMSCfg.EnableEventData;
        this.saveFAULTMidnightTXT = this.saveMeterCONFIGpageJSON.DATA.DLMSCfg.EnableMidnightData;
        this.saveFAULTBillingTXT = this.saveMeterCONFIGpageJSON.DATA.DLMSCfg.EnableBillingData;
        this.saveSERIALMidnightPeriodTXT = this.saveMeterCONFIGpageJSON.DATA.DLMSCfg.MidnightPollPer;
        this.saveFAULTMBillingPeriodTXT = this.saveMeterCONFIGpageJSON.DATA.DLMSCfg.BillingPollPer;
        for (var portindex = 0; portindex < parseInt(this.saveDeviceCONFIGpageJSON.DATA.SerPortCfg.NumSerPorts); portindex++) {
          document.getElementById('saveFAULTCommModetTXT' + (portindex + 1)).innerHTML = this.saveDeviceCONFIGpageJSON.DATA.SerPortCfg.PortCfg[portindex].InfMode;

          document.getElementById('saveFAULTbaudrateTXT' + (portindex + 1)).innerHTML = this.saveDeviceCONFIGpageJSON.DATA.SerPortCfg.PortCfg[portindex].BaudRate;
          document.getElementById('saveFAULTstopbitsTXT' + (portindex + 1)).innerHTML = this.saveDeviceCONFIGpageJSON.DATA.SerPortCfg.PortCfg[portindex].Stopbits;
          document.getElementById('saveFAULTparityTXT' + (portindex + 1)).innerHTML = this.saveDeviceCONFIGpageJSON.DATA.SerPortCfg.PortCfg[portindex].Parity;
          document.getElementById('saveFAULTdataTXT' + (portindex + 1)).innerHTML = this.saveDeviceCONFIGpageJSON.DATA.SerPortCfg.PortCfg[portindex].Databits;
        }
      }

      this.saveinstselectedParamsList = this.saveParamsINSTelectedJSON.DATA.InstParams.ObisCodeList;
      this.saveloadserveselectedParamsList = this.saveParamsLSelectedJSON.DATA.LSParams.ObisCodeList;
      this.saveeventselectedParamsList = this.saveParamsEVENTCONFIGpageJSON.DATA.EventParams.ObisCodeList;
      this.savemidnightselectedParamsList = this.saveParamsMNCONFIGpageJSON.DATA.MNParams.ObisCodeList;
      this.savebillingselectedParamsList = this.saveParamsBILLCONFIGpageJSON.DATA.BillParams.ObisCodeList;
    },
    saveDCUfuntion: function saveDCUfuntion() {
      var _this2 = this;

      var alertval = confirm('Do you want save all configuration?');
      if (alertval) {
        var RespData = '';
        console.log("-------CLICK SAVE BUTTON----------");
        this.ws = new WebSocket(this.webSocketUrl);
        this.ws.onopen = function (e) {
          _this2.clicksave = true;
          var checkGEN = _.isEqual(_this2.$session.get('get_GenconfigJSON'), _this2.$session.get('get_copy_GenconfigJSON'));
          if (!checkGEN) {
            var setGENconfigJSON = _this2.$session.get('get_GenconfigJSON');
            setGENconfigJSON.CMD_TYPE = 'SET_GEN_CONFIG';
            console.log(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(setGENconfigJSON));
            _this2.ws.send(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(setGENconfigJSON));
          }
          var checkUPSTREAM = _.isEqual(_this2.$session.get('get_UpstreamconfigJSON'), _this2.$session.get('get_copy_UpstreamconfigJSON'));
          if (!checkUPSTREAM) {
            var setUPSTREAMconfigJSON = _this2.$session.get('get_UpstreamconfigJSON');
            setUPSTREAMconfigJSON.CMD_TYPE = 'SET_UPSTREAM_CONFIG';
            console.log(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(setUPSTREAMconfigJSON));
            _this2.ws.send(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(setUPSTREAMconfigJSON));
          }
          var checkDLMS = _.isEqual(_this2.$session.get('get_DlmsMeterconfigSON'), _this2.$session.get('get_copy_DlmsMeterconfigSON'));
          if (!checkDLMS) {
            var setDLMSMeterconfigJSON = _this2.$session.get('get_DlmsMeterconfigSON');
            setDLMSMeterconfigJSON.CMD_TYPE = 'SET_DLMS_CONFIG';
            console.log(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(setDLMSMeterconfigJSON));
            _this2.ws.send(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(setDLMSMeterconfigJSON));
          }
          var checkINST = _.isEqual(_this2.$session.get('get_SelectedINSTJSON'), _this2.$session.get('get_copy_SelectedINSTJSON'));
          if (!checkINST) {
            var setSelInstconfigJSON = _this2.$session.get('get_SelectedINSTJSON');
            setSelInstconfigJSON.CMD_TYPE = 'SET_DLMS_INST_PARAM_CONFIG';
            console.log(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(setSelInstconfigJSON));
            _this2.ws.send(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(setSelInstconfigJSON));
          }
          var checkLS = _.isEqual(_this2.$session.get('get_SelectedLSJSON'), _this2.$session.get('get_copy_SelectedLSJSON'));
          if (!checkLS) {
            var setSelLSconfigJSON = _this2.$session.get('get_SelectedLSJSON');
            setSelLSconfigJSON.CMD_TYPE = 'SET_DLMS_LS_PARAM_CONFIG';
            console.log(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(setSelLSconfigJSON));
            _this2.ws.send(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(setSelLSconfigJSON));
          }
          var checkMN = _.isEqual(_this2.$session.get('get_SelectedMNJSON'), _this2.$session.get('get_copy_SelectedMNJSON'));
          if (!checkMN) {
            var setSelMNconfigJSON = _this2.$session.get('get_SelectedMNJSON');
            setSelMNconfigJSON.CMD_TYPE = 'SET_DLMS_MN_PARAM_CONFIG';
            console.log(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(setSelMNconfigJSON));
            _this2.ws.send(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(setSelMNconfigJSON));
          }
          var checkEVENT = _.isEqual(_this2.$session.get('get_SelectedEVENTJSON'), _this2.$session.get('get_copy_SelectedEVENTJSON'));
          if (!checkEVENT) {
            var setSelEVENTconfigJSON = _this2.$session.get('get_SelectedEVENTJSON');
            setSelEVENTconfigJSON.CMD_TYPE = 'SET_DLMS_EVENT_PARAM_CONFIG';
            console.log(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(setSelEVENTconfigJSON));
            _this2.ws.send(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(setSelEVENTconfigJSON));
          }
          var checkBILL = _.isEqual(_this2.$session.get('get_SelectedBILLJSON'), _this2.$session.get('get_copy_SelectedBILLJSON'));
          if (!checkBILL) {
            var setSelBILLconfigJSON = _this2.$session.get('get_SelectedBILLJSON');
            setSelBILLconfigJSON.CMD_TYPE = 'SET_DLMS_BILL_PARAM_CONFIG';
            console.log(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(setSelBILLconfigJSON));
            _this2.ws.send(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(setSelBILLconfigJSON));
          }
          var saveapplyCFG = { "TYPE": "CMD_MESSAGE", "SEQ_NUM": Math.floor(1000 + Math.random() * 9000).toString(), "CMD_TYPE": "SAVENAPPLY_CFG" };
          _this2.ws.send(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(saveapplyCFG));
        };
        this.ws.onmessage = function (e) {
          console.log("-------SAVE recv----------" + __WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(e.data));
          if (e.data.length == 4096) {
            RespData = RespData + e.data;
          } else {
            RespData = RespData + e.data;
            try {
              var split_char = RespData.split('!');
              var count = split_char.length - 1;
              for (var idx = 0; idx < count; idx++) {
                var savewebsocketBody = JSON.parse(split_char[idx]);
                RespData = '';
                if (savewebsocketBody.TYPE == "SAVENAPPLY_CFG" && savewebsocketBody.CMD_STATUS == "SUCCESS") {
                  _this2.blockdevice = true;
                  _this2.toggleTimer();
                  setTimeout(_this2.clearALLSession1, _this2.durationlimit);
                }
              }
            } catch (err) {
              RespData = '';
              console.log("Invalid data");
              console.log(err);
            }
          }
        };
      }
    },
    toggleTimer: function toggleTimer() {
      if (this.isRunning) {
        clearInterval(this.interval);
      } else {
        this.interval = setInterval(this.incrementTime, 1000);
      }
      this.isRunning = !this.isRunning;
    },
    incrementTime: function incrementTime() {
      this.time = parseInt(this.time) - 1;
    },
    clearALLSession1: function clearALLSession1() {
      this.blockdevice = false;
      this.$session.clear("loginsession");
      this.$session.clear("UserRole");
      this.$session.clear("get_GenconfigJSON");
      this.$session.clear("get_UpstreamconfigJSON");
      this.$session.clear("get_DlmsMeterconfigSON");
      this.$session.clear("get_MasterINSTJSON");
      this.$session.clear("get_MasterLSJSON");
      this.$session.clear("get_MasterMNJSON");
      this.$session.clear("get_MasterEVENTJSON");
      this.$session.clear("get_MasterBILLJSON");
      this.$session.clear("get_SelectedINSTJSON");
      this.$session.clear("get_SelectedLSJSON");
      this.$session.clear("get_SelectedMNJSON");
      this.$session.clear("get_SelectedEVENTJSON");
      this.$session.clear("get_SelectedBILLJSON");

      this.$session.clear("get_copy_GenconfigJSON");
      this.$session.clear("get_copy_UpstreamconfigJSON");
      this.$session.clear("get_copy_DlmsMeterconfigSON");
      this.$session.clear("get_copy_MasterINSTJSON");
      this.$session.clear("get_copy_MasterLSJSON");
      this.$session.clear("get_copy_MasterMNJSON");
      this.$session.clear("get_copy_MasterEVENTJSON");
      this.$session.clear("get_copy_MasterBILLJSON");
      this.$session.clear("get_copy_SelectedINSTJSON");
      this.$session.clear("get_copy_SelectedLSJSON");
      this.$session.clear("get_copy_SelectedMNJSON");
      this.$session.clear("get_copy_SelectedEVENTJSON");
      this.$session.clear("get_copy_SelectedBILLJSON");
      this.$router.replace({ path: '/' });
    },

    isNumber: function isNumber(evt) {
      evt = evt ? true : window.event;
      var charCode = evt.which ? evt.which : evt.keyCode;
      if (charCode > 31 && (charCode < 48 || charCode > 57) && charCode !== 46) {
        evt.preventDefault();
      } else {
        return true;
      }
    },
    successMessage: function successMessage(msg) {
      this.$notice.success({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    warningMessage: function warningMessage(msg) {
      this.$notice.warning({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    infoMessage: function infoMessage(msg) {
      this.$notice.info({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    errorMessage: function errorMessage(msg) {
      this.$notice.error({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    }
  }
});

/***/ }),
/* 48 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
Object.defineProperty(__webpack_exports__, "__esModule", { value: true });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_crip_vue_notice__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_crip_vue_notice___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_0_crip_vue_notice__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_vue_element_loading__ = __webpack_require__(2);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_vue_element_loading___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_1_vue_element_loading__);




/* harmony default export */ __webpack_exports__["default"] = ({
  name: 'GeneralSetting',
  components: {
    CripNotice: __WEBPACK_IMPORTED_MODULE_0_crip_vue_notice___default.a,
    VueElementLoading: __WEBPACK_IMPORTED_MODULE_1_vue_element_loading___default.a
  },
  data: function data() {
    return {
      isLoading: false,
      username: 'admin',
      password: 'softel',
      adminusernameTXT: '',
      adminpasswordTXT: '',
      admindescripSAVEHeightData: 0,
      adminDesArray: []
    };
  },
  created: function created() {
    if (this.$session.get("loginsession") == "") {
      this.$router.replace({ path: '/' });
      return false;
    }
  },
  mounted: function mounted() {
    var _this = this;

    this.isLoading = true;
    var innerMinHeight = window.innerHeight - 122 + 'px';
    document.getElementById('uploadFirmwarepane').style.minHeight = innerMinHeight;
    setTimeout(function () {
      return _this.isLoading = false;
    }, 200);
  },

  methods: {
    beforeOpen: function beforeOpen() {},
    beforeClose: function beforeClose() {},
    opened: function opened(e) {},
    closed: function closed(e) {},
    viewServiceMethod: function viewServiceMethod() {
      this.warningMessage('Not available');
      return false;
    },
    openAdminpopupMethod: function openAdminpopupMethod() {
      this.$modal.show('adminLoginpopup');
      this.adminusernameTXT = '';
      this.adminpasswordTXT = '';
    },
    adminLoginpopupclose: function adminLoginpopupclose() {
      this.$modal.hide('adminLoginpopup');
    },
    adminLoginMethod: function adminLoginMethod() {
      if (this.adminusernameTXT === '') {
        this.warningMessage('Please enter a user name.');
        return false;
      }
      if (this.adminpasswordTXT === '') {
        this.warningMessage('Please enter a password.');
        return false;
      }
      if (this.adminusernameTXT === this.username && this.adminpasswordTXT === this.password) {
        this.successMessage('Admin login successfully.');
        this.$modal.hide('adminLoginpopup');
        this.admindescripSAVEHeightData = window.innerHeight - 400;
        this.$modal.show('addAdmindescriptionPopup');
        this.adminDesArray = [];
        this.adminDesArray.push({ date: this.getdateformat(new Date()), description: '', person: '' });
        return false;
      } else {
        this.errorMessage('Incorrect user name and password.');
        return false;
      }
    },
    addAdmindescriptionPopupclose: function addAdmindescriptionPopupclose() {
      this.$modal.hide('addAdmindescriptionPopup');
    },
    addAdmindescriptionSAVEMethod: function addAdmindescriptionSAVEMethod() {
      this.$modal.hide('addAdmindescriptionPopup');
      this.successMessage('service history saved successfully.');
      return false;
    },
    changeDecsTextareaFunction: function changeDecsTextareaFunction(rowIndex) {
      this.adminDesArray[rowIndex].description = document.getElementById('descTXTid' + rowIndex).value;
    },
    changepersonTextFunction: function changepersonTextFunction(rowIndex) {
      this.adminDesArray[rowIndex].person = document.getElementById('personTXTid' + rowIndex).value;
    },
    adddesrowMethod: function adddesrowMethod() {
      this.adminDesArray.push({ date: this.getdateformat(new Date()), description: '', person: '' });
    },
    admindescDeleteBTNFunction: function admindescDeleteBTNFunction(rowIndex) {
      this.adminDesArray.splice(rowIndex, 1);
    },
    getdateformat: function getdateformat(date) {
      var dtToday = new Date(date);
      var month = dtToday.getMonth() + 1;
      var day = dtToday.getDate();
      var year = dtToday.getFullYear();
      var replcema = year;
      if (month < 10) {
        month = '0' + month;
      }
      if (day < 10) {
        day = '0' + day;
      }
      var returndate = replcema.toString().replace('-', '') + '-' + month + '-' + day;
      return returndate;
    },

    isNumber: function isNumber(evt) {
      evt = evt ? true : window.event;
      var charCode = evt.which ? evt.which : evt.keyCode;
      if (charCode > 31 && (charCode < 48 || charCode > 57) && charCode !== 46) {
        evt.preventDefault();
      } else {
        return true;
      }
    },
    successMessage: function successMessage(msg) {
      this.$notice.success({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    warningMessage: function warningMessage(msg) {
      this.$notice.warning({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    infoMessage: function infoMessage(msg) {
      this.$notice.info({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    errorMessage: function errorMessage(msg) {
      this.$notice.error({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    }
  }
});

/***/ }),
/* 49 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
Object.defineProperty(__webpack_exports__, "__esModule", { value: true });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify__ = __webpack_require__(3);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_crip_vue_notice__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_crip_vue_notice___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_1_crip_vue_notice__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2_vue_element_loading__ = __webpack_require__(2);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2_vue_element_loading___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_2_vue_element_loading__);





/* harmony default export */ __webpack_exports__["default"] = ({
  name: "UploadFirmware",
  components: {
    CripNotice: __WEBPACK_IMPORTED_MODULE_1_crip_vue_notice___default.a,
    VueElementLoading: __WEBPACK_IMPORTED_MODULE_2_vue_element_loading___default.a
  },
  data: function data() {
    return {
      isLoading: false,
      deviceStatustableheight: 0,
      divLength: 6,
      countlength: 0,
      getmeterStatusArray: [],
      getmeterStatuspopupTitle: "",
      getmeterStatuspopupLocation: "",
      getmeterStatuspopupSerialNum: "",
      getmeterStatuspopupCommStatus: "",
      getmeterStatuspopupUpdateTime: "",
      instaLLJSon: "",
      meterstatusInterval: ""
    };
  },
  created: function created() {
    var _this = this;

    if (this.$session.get("loginsession") == "") {
      this.$router.replace({ path: "/" });
      return false;
    }
    this.isLoading = true;
    var RespData = "";
    this.ws = new WebSocket(this.webSocketUrl);
    this.ws.onopen = function (e) {
      _this.meterstatusInterval = setInterval(function () {
        var commdObj1 = {
          TYPE: "CYCLIC_MESSAGE",
          SEQ_NUM: Math.floor(1000 + Math.random() * 9000).toString(),
          CMD_TYPE: "CYCLIC_INST"
        };
        _this.ws.send(__WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(commdObj1));
      }, 3000);
    };
    this.ws.onmessage = function (e) {
      console.log("status page :start::" + __WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(e.data));
      try {
        if (e.data.length == 4096) {
          RespData = RespData + e.data;
        } else {
          RespData = RespData + e.data;
          try {
            var split_char = RespData.split("!");
            var count = split_char.length - 1;
            for (var idx = 0; idx < count; idx++) {
              var websocketBody = JSON.parse(split_char[idx]);
              RespData = "";
              console.log("status page correct data");
              console.log("status page :msg::" + __WEBPACK_IMPORTED_MODULE_0_babel_runtime_core_js_json_stringify___default()(websocketBody));
              if (websocketBody.TYPE == "CYCLIC_MESSAGE") {
                _this.instaLLJSon = "";
                _this.instaLLJSon = websocketBody;
                _this.isLoading = false;
              }
            }
          } catch (err) {
            RespData = "";
            console.log("Invalid data");
            console.log(err);
          }
        }
      } catch (err) {}
    };
  },
  mounted: function mounted() {

    var innerMinHeight = window.innerHeight - 140 + "px";
    this.deviceStatustableheight = window.innerHeight - 330 + "px";
    document.getElementById("deviceStatuspane").style.minHeight = innerMinHeight;
  },
  destroyed: function destroyed() {
    this.ws.close();
    clearInterval(this.meterstatusInterval);
  },

  methods: {
    beforeOpen: function beforeOpen() {},
    beforeClose: function beforeClose() {},
    meterstatuspopupopened: function meterstatuspopupopened() {
      this.$modal.show("meterstatuspopup");
    },
    meterstatuspopupclosed: function meterstatuspopupclosed() {
      this.$modal.hide("meterstatuspopup");
    },

    isNumber: function isNumber(evt) {
      evt = evt ? true : window.event;
      var charCode = evt.which ? evt.which : evt.keyCode;
      if (charCode > 31 && (charCode < 48 || charCode > 57) && charCode !== 46) {
        evt.preventDefault();
      } else {
        return true;
      }
    },
    getmeterStatus: function getmeterStatus(rowIndex) {
      this.getmeterStatuspopupTitle = "";
      this.getmeterStatuspopupLocation = "";
      this.getmeterStatuspopupSerialNum = "";
      this.getmeterStatuspopupCommStatus = "";
      this.getmeterStatuspopupUpdateTime = "";
      this.getmeterStatusArray = [];
      if (this.instaLLJSon.DATA.INST_PARAM[rowIndex - 1].PARAMS.length != 0) {
        this.getmeterStatuspopupLocation = this.instaLLJSon.DATA.INST_PARAM[rowIndex - 1].MET_LOC;
        this.getmeterStatuspopupSerialNum = this.instaLLJSon.DATA.INST_PARAM[rowIndex - 1].MET_SERNUM;
        if (this.instaLLJSon.DATA.INST_PARAM[rowIndex - 1].COMM_STATUS == "0") {
          this.getmeterStatuspopupCommStatus = "Not Communicating";
        } else if (this.instaLLJSon.DATA.INST_PARAM[rowIndex - 1].COMM_STATUS == "1") {
          this.getmeterStatuspopupCommStatus = "Communicating";
        } else {
          this.getmeterStatuspopupCommStatus = "Not Configured";
        }
        this.getmeterStatuspopupUpdateTime = this.instaLLJSon.DATA.INST_PARAM[rowIndex - 1].UPDATE_TIME;
        this.getmeterStatusArray = this.instaLLJSon.DATA.INST_PARAM[rowIndex - 1].PARAMS;
        var tableCount1 = parseInt(this.getmeterStatusArray.length / this.divLength + (this.getmeterStatusArray.length % this.divLength == 0 ? 0 : 1));
        this.countlength = tableCount1;
        this.meterstatuspopupopened();
      } else {
        alert("Data Not found");
        return false;
      }
    },
    meterStatuspopupclse: function meterStatuspopupclse() {},
    showGetFormattedDatewithTime: function showGetFormattedDatewithTime(date) {
      var month = date.getMonth() + 1;
      var day = date.getDate();
      var year = date.getFullYear();
      var seconds = date.getSeconds() <= 9 ? "0" + date.getSeconds() : date.getSeconds();
      var minutes = date.getMinutes() <= 9 ? "0" + date.getMinutes() : date.getMinutes();
      var hour = date.getHours() <= 9 ? "0" + date.getHours() : date.getHours();
      var monthStr = month <= 9 ? "0" + month : month;
      var dateStr = day <= 9 ? "0" + day : day;
      return dateStr + "-" + monthStr + "-" + year + " " + hour + ":" + minutes + ":" + seconds;
    },
    successMessage: function successMessage(msg) {
      this.$notice.success({
        title: "Notification",
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    warningMessage: function warningMessage(msg) {
      this.$notice.warning({
        title: "Notification",
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    infoMessage: function infoMessage(msg) {
      this.$notice.info({
        title: "Notification",
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    errorMessage: function errorMessage(msg) {
      this.$notice.error({
        title: "Notification",
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    }
  }
});

/***/ }),
/* 50 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
Object.defineProperty(__webpack_exports__, "__esModule", { value: true });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_crip_vue_notice__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_crip_vue_notice___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_0_crip_vue_notice__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_vue_element_loading__ = __webpack_require__(2);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_vue_element_loading___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_1_vue_element_loading__);




/* harmony default export */ __webpack_exports__["default"] = ({
  name: 'UploadFirmware',
  components: {
    CripNotice: __WEBPACK_IMPORTED_MODULE_0_crip_vue_notice___default.a,
    VueElementLoading: __WEBPACK_IMPORTED_MODULE_1_vue_element_loading___default.a
  },
  data: function data() {
    return {
      isLoading: false,
      file1: '',
      file2: ''
    };
  },
  created: function created() {
    if (this.$session.get("loginsession") == "") {
      this.$router.replace({ path: '/' });
      return false;
    }
  },
  mounted: function mounted() {
    var _this = this;

    this.isLoading = true;
    var innerMinHeight = window.innerHeight - 122 + 'px';
    document.getElementById('uploadFirmwarepane').style.minHeight = innerMinHeight;
    setTimeout(function () {
      return _this.isLoading = false;
    }, 500);
  },

  methods: {
    handleFile1Upload: function handleFile1Upload() {
      this.file1 = this.$refs.file1.files[0];
    },
    submitFile1: function submitFile1() {
      if (this.file1 === undefined || this.file1 === '') {
        this.warningMessage('Please upload the config file and proceed further.');
        return false;
      }
      this.isLoading = true;
      var read = new FileReader();
      read.readAsArrayBuffer(this.file1);
      read.onloadend = function () {
        var xmlhttp = new XMLHttpRequest();
        var urlData = window.location.protocol + '//' + window.location.host + '/' + 'cgi-bin/uploadconfig.cgi';
        xmlhttp.onreadystatechange = function () {
          if (xmlhttp.readyState === 4 && xmlhttp.status === 200) {
            try {
              var DataObj = JSON.parse(xmlhttp.responseText);
              if (DataObj.status === 'success') {} else {}
            } catch (error) {
              this.isLoading = false;
              alert(error);
            }
          }
        };
        xmlhttp.open('POST', urlData, false);

        xmlhttp.setRequestHeader('Cache-Control', 'no-cache');
        xmlhttp.send(read.result);
      };
    },
    handleFile2Upload: function handleFile2Upload() {
      this.file2 = this.$refs.file2.files[0];
    },
    submitFile2: function submitFile2() {
      if (this.file2 === undefined || this.file2 === '') {
        this.warningMessage('Please upload the firmware and proceed further.');
        return false;
      }
      this.isLoading = true;
      var read = new FileReader();
      read.readAsArrayBuffer(this.file2);
      read.onloadend = function () {
        var xmlhttp = new XMLHttpRequest();
        var urlData = window.location.protocol + '//' + window.location.host + '/' + 'cgi-bin/uploadconfig.cgi';
        xmlhttp.onreadystatechange = function () {
          if (xmlhttp.readyState === 4 && xmlhttp.status === 200) {
            try {
              var DataObj = JSON.parse(xmlhttp.responseText);
              if (DataObj.status === 'success') {} else {}
            } catch (error) {
              this.isLoading = false;
              alert(error);
            }
          }
        };
        xmlhttp.open('POST', urlData, false);

        xmlhttp.setRequestHeader('Cache-Control', 'no-cache');
        xmlhttp.send(read.result);
      };
    },

    isNumber: function isNumber(evt) {
      evt = evt ? true : window.event;
      var charCode = evt.which ? evt.which : evt.keyCode;
      if (charCode > 31 && (charCode < 48 || charCode > 57) && charCode !== 46) {
        evt.preventDefault();
      } else {
        return true;
      }
    },
    successMessage: function successMessage(msg) {
      this.$notice.success({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    warningMessage: function warningMessage(msg) {
      this.$notice.warning({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    infoMessage: function infoMessage(msg) {
      this.$notice.info({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    errorMessage: function errorMessage(msg) {
      this.$notice.error({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    }
  }
});

/***/ }),
/* 51 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
Object.defineProperty(__webpack_exports__, "__esModule", { value: true });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_crip_vue_notice__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_crip_vue_notice___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_0_crip_vue_notice__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_vue_element_loading__ = __webpack_require__(2);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_vue_element_loading___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_1_vue_element_loading__);




/* harmony default export */ __webpack_exports__["default"] = ({
  name: 'UpstreamConfig',
  components: {
    CripNotice: __WEBPACK_IMPORTED_MODULE_0_crip_vue_notice___default.a,
    VueElementLoading: __WEBPACK_IMPORTED_MODULE_1_vue_element_loading___default.a
  },
  data: function data() {
    return {
      deviceCONFIGPageJSON: this.$session.get("get_GenconfigJSON"),
      upStreamCONFIGPageJSON: this.$session.get("get_UpstreamconfigJSON"),
      dlmsmeterCONFIGPageJSON: this.$session.get("get_DlmsMeterconfigSON"),
      masterINSTCONFIGjSON: this.$session.get("get_MasterINSTJSON"),
      masterLSCONFIGjSON: this.$session.get("get_MasterLSJSON"),
      masterMNCONFIGjSON: this.$session.get("get_MasterMNJSON"),
      masterEVENTCONFIGjSON: this.$session.get("get_MasterEVENTJSON"),
      masterBILLCONFIGjSON: this.$session.get("get_MasterBILLJSON"),
      paramSelINSTCONFIGjSON: this.$session.get("get_SelectedINSTJSON"),
      paramSelLSCONFIGjSON: this.$session.get("get_SelectedLSJSON"),
      paramSelMNCONFIGjSON: this.$session.get("get_SelectedMNJSON"),
      paramSelEVENTCONFIGjSON: this.$session.get("get_SelectedEVENTJSON"),
      paramSelBILLCONFIGjSON: this.$session.get("get_SelectedBILLJSON"),
      isLoading: false,
      fullPage: true,
      gendculocTXT: '',
      genrestimeoutTXT: '2',
      genreadsurveyTXT: 'Yes',
      gencommProtocolTXT: 'IEC104',
      lancurrIpTXT: '',
      lannewIpTXT: '',
      lansubnetmaskIpTXT: '',
      langatewayIpTXT: '',
      lancurrIp2TXT: '',
      lannewIp2TXT: '',
      lansubnetmaskIp2TXT: '',
      langatewayIp2TXT: '',
      ethcount: '2',
      iec104Enablechekbox: false,
      ftpEnablechekbox: false,
      ftpIpaddTXT: '',
      ftpprtnoTXT: '',
      ftpusernameTXT: '',
      ftppasswordTXT: '',
      ftpdirTXT: '',
      ftptimeoutTXT: '15',
      ftpLOGEnablechekbox: false,
      ftpLOGIpaddTXT: '',
      ftpLOGprtnoTXT: '',
      ftpLOGusernameTXT: '',
      ftpLOGpasswordTXT: '',
      ftpLOGdirTXT: '',
      ftpLOGtimeoutTXT: '15',
      mqttEnablecheckbox: false,
      enethernet1Checkbox: true,
      enethernet2Checkbox: false,
      lancurrentipaddressTXT: '',
      genLANNewIPTXT: '',
      gensubnetMaskIPTXT: '',
      genGatewayaddressIPTXT: '',
      lancurrentipaddressTXT2: '',
      genLANNewIPTXT2: '',
      gensubnetMaskIPTXT2: '',
      genGatewayaddressIPTXT2: '',
      gendebugipcheckbox: false,
      gendebugIPTXT: '',
      mbEnablechekbox: false,
      mbUsernameTXT: '',
      mbPasswordTXT: '',
      mbPhoneTXT: '',
      mbAPNTXT: '',
      mbEnablenethealthchekbox: false,
      mbPingIPTXT: '',
      mbPingIntervalTXT: '',
      mbNumofPingTXT: '',
      ntpStatedwnTXT1: 'Choose State',
      ntpserverIPAddressTXT1: '',
      ntpserverPortTXT1: '',
      ntpStatedwnTXT2: 'Choose State',
      ntpserverIPAddressTXT2: '',
      ntpserverPortTXT2: '',
      ntpserverIntervalTXT: '',
      ntpservercommnicationdwnTXT: 'Choose Protocol',
      iecStationTXT: '',
      startIOAaddTXT: '',
      iecCodsizedwnTXT: 'Choose COT Size',
      iecCylicTXT: '',
      iecIOAsizedwnTXT: 'Choose IOA Size',
      iecTSTAdwnTXT: 'Choose TSTA',
      iecTSTAstartAddresTXT: '',
      iecTimeout1TXT: '',
      iecTimeout2TXT: '',
      iecTimeout3TXT: '',
      iecportTXT: '',
      allowMastercheckbox: false,
      allowMastercheckbox1: false,
      allowMastercheckbox2: false,
      allowMastercheckbox3: false,
      allowMastercheckbox4: false,
      allowMasterTXT1: '',
      allowMasterTXT2: '',
      allowMasterTXT3: '',
      allowMasterTXT4: '',
      modTcpEnablechekbox: false,
      modTCPdeVidTXT: '',
      RespToAllSlaveIdTXT: '',
      modTCPprtnoTXT: '502',
      modTCPholdstartAddTXT: '',
      modTCPinputstartAddTXT: '',
      modTCPDiscriteinputstartAddTXT: '',
      mqttBrokerIpTXT: '',
      mqttBrokerPortTXT: '',
      mqttBrokerUserNameTXT: '',
      mqttBrokerPasswordTXT: '',
      mqttBrokerCycDataTopicTXT: '',
      mqttBrokerCmdTopicTXT: '',
      mqttEnableEventTopicTXT: false,
      mqttEventTopicTXT: '',
      mqttEnableDiagTopicTXT: false,
      mqttDiagTopicTXT: '',
      mqttPeriodTXT: '',
      cmsEMSEnablecheckbox: false,
      cmsemsEnableIPTXT: '',
      cmsemsEnableportNoTXT: '',
      cmsemsEnableEvent: '',
      cmsemsEnableDiag: '',
      cmsemsPeriodTXT: ''
    };
  },
  mounted: function mounted() {
    var _this = this;

    this.isLoading = true;
    var innerMinHeight = window.innerHeight - 130 + 'px';
    document.getElementById('UpstreamConfigPagePANE').style.minHeight = innerMinHeight;
    setTimeout(function () {
      return _this.isLoading = false;
    }, 500);
  },
  created: function created() {
    if (this.$session.get("loginsession") == "") {
      this.$router.replace({ path: '/' });
      return false;
    }
    this.upStreampageLoad();
  },

  updated: function updated() {
    this.saveUpstremConfig();
  },
  beforeDestroy: function beforeDestroy() {
    this.upStreampConfigPageValidation();
  },

  methods: {
    upStreampConfigPageValidation: function upStreampConfigPageValidation() {
      if (this.iec104Enablechekbox) {
        if (this.iecStationTXT === "" || this.iecStationTXT === null) {
          this.warningMessage("Please enter a station address");
          this.$router.replace({ path: '/dcu/upstreamconfig' });
          return false;
        }
        if (this.iecportTXT === "" || this.iecportTXT === null) {
          this.warningMessage("Please enter a port number");
          this.$router.replace({ path: '/dcu/upstreamconfig' });
          return false;
        }
        if (this.iecCylicTXT === "" || this.iecCylicTXT === null) {
          this.warningMessage("Please enter a cylic");
          this.$router.replace({ path: '/dcu/upstreamconfig' });
          return false;
        }
        if (this.startIOAaddTXT === "" || this.startIOAaddTXT === null) {
          this.warningMessage("Please enter a start io address");
          this.$router.replace({ path: '/dcu/upstreamconfig' });
          return false;
        }
        if (this.iecCodsizedwnTXT === "" || this.iecCodsizedwnTXT === null) {
          this.warningMessage("Please choose any one COT");
          this.$router.replace({ path: '/dcu/upstreamconfig' });
          return false;
        }
        if (this.iecIOAsizedwnTXT === "" || this.iecIOAsizedwnTXT === null) {
          this.warningMessage("Please choose any one IOA");
          this.$router.replace({ path: '/dcu/upstreamconfig' });
          return false;
        }
      }
      if (this.allowMastercheckbox) {
        if (this.allowMastercheckbox1) {
          if (this.allowMasterTXT1 === "" || this.allowMasterTXT1 === null) {
            this.warningMessage("Please enter a master 1");
            this.$router.replace({ path: '/dcu/upstreamconfig' });
            return false;
          }
        }
        if (this.allowMastercheckbox2) {
          if (this.allowMasterTXT2 === "" || this.allowMasterTXT2 === null) {
            this.warningMessage("Please enter a master 2");
            this.$router.replace({ path: '/dcu/upstreamconfig' });
            return false;
          }
        }
        if (this.allowMastercheckbox3) {
          if (this.allowMasterTXT3 === "" || this.allowMasterTXT3 === null) {
            this.warningMessage("Please enter a master 3");
            this.$router.replace({ path: '/dcu/upstreamconfig' });
            return false;
          }
        }
        if (this.allowMastercheckbox4) {
          if (this.allowMasterTXT4 === "" || this.allowMasterTXT4 === null) {
            this.warningMessage("Please enter a master 4");
            this.$router.replace({ path: '/dcu/upstreamconfig' });
            return false;
          }
        }
      }

      if (this.ftpEnablechekbox) {
        if (this.ftpIpaddTXT === "" || this.ftpIpaddTXT === null) {
          this.warningMessage("Please enter a ftp ip address");
          this.$router.replace({ path: '/dcu/upstreamconfig' });
          return false;
        }
        var bool22 = this.ValidateIPaddress(this.ftpIpaddTXT);
        if (!bool22) {
          this.warningMessage("You have entered ftp ip address is invalid IP address!");
          this.$router.replace({ path: '/dcu/deviceconfig' });
          return false;
        }
        if (this.ftpprtnoTXT === "" || this.ftpprtnoTXT === null) {
          this.warningMessage("Please enter a ftp port number");
          this.$router.replace({ path: '/dcu/upstreamconfig' });
          return false;
        }
        if (this.ftpusernameTXT === "" || this.ftpusernameTXT === null) {
          this.warningMessage("Please enter a ftp user name");
          this.$router.replace({ path: '/dcu/upstreamconfig' });
          return false;
        }
        if (this.ftppasswordTXT === "" || this.ftppasswordTXT === null) {
          this.warningMessage("Please enter a ftp password");
          this.$router.replace({ path: '/dcu/upstreamconfig' });
          return false;
        }
        if (this.ftpdirTXT === "" || this.ftpdirTXT === null) {
          this.warningMessage("Please enter a ftp directory");
          this.$router.replace({ path: '/dcu/upstreamconfig' });
          return false;
        }
        if (this.ftptimeoutTXT === "" || this.ftptimeoutTXT === null) {
          this.warningMessage("Please choose any one ftp time interval");
          this.$router.replace({ path: '/dcu/upstreamconfig' });
          return false;
        }

        if (this.ftpLOGEnablechekbox) {
          if (this.ftpLOGIpaddTXT === "" || this.ftpLOGIpaddTXT === null) {
            this.warningMessage("Please enter a ftp log ip address");
            this.$router.replace({ path: '/dcu/upstreamconfig' });
            return false;
          }
          var bool22 = this.ValidateIPaddress(this.ftpLOGIpaddTXT);
          if (!bool22) {
            this.warningMessage("You have entered ftp log ip address is invalid IP address!");
            this.$router.replace({ path: '/dcu/deviceconfig' });
            return false;
          }
          if (this.ftpLOGprtnoTXT === "" || this.ftpLOGprtnoTXT === null) {
            this.warningMessage("Please enter a ftp log port number");
            this.$router.replace({ path: '/dcu/upstreamconfig' });
            return false;
          }
          if (this.ftpLOGusernameTXT === "" || this.ftpLOGusernameTXT === null) {
            this.warningMessage("Please enter a ftp log user name");
            this.$router.replace({ path: '/dcu/upstreamconfig' });
            return false;
          }
          if (this.ftpLOGpasswordTXT === "" || this.ftpLOGpasswordTXT === null) {
            this.warningMessage("Please enter a ftp log password");
            this.$router.replace({ path: '/dcu/upstreamconfig' });
            return false;
          }
          if (this.ftpLOGdirTXT === "" || this.ftpLOGdirTXT === null) {
            this.warningMessage("Please enter a ftp log directory");
            this.$router.replace({ path: '/dcu/upstreamconfig' });
            return false;
          }
          if (this.ftpLOGtimeoutTXT === "" || this.ftpLOGtimeoutTXT === null) {
            this.warningMessage("Please choose any one ftp log time interval");
            this.$router.replace({ path: '/dcu/upstreamconfig' });
            return false;
          }
        }
      }

      if (this.modTcpEnablechekbox) {
        if (this.modTCPdeVidTXT === "" || this.modTCPdeVidTXT === null) {
          this.warningMessage("Please enter a mod tcp device id");
          this.$router.replace({ path: '/dcu/upstreamconfig' });
          return false;
        }
        if (this.RespToAllSlaveIdTXT === "" || this.RespToAllSlaveIdTXT === null) {
          this.warningMessage("Please enter a mod tcp RespToAllSlaveId");
          this.$router.replace({ path: '/dcu/upstreamconfig' });
          return false;
        }
        if (this.modTCPprtnoTXT === "" || this.modTCPprtnoTXT === null) {
          this.warningMessage("Please enter a mod tcp port number");
          this.$router.replace({ path: '/dcu/upstreamconfig' });
          return false;
        }
        if (this.modTCPholdstartAddTXT === "" || this.modTCPholdstartAddTXT === null) {
          this.warningMessage("Please enter a mod tcp hold register start address");
          this.$router.replace({ path: '/dcu/upstreamconfig' });
          return false;
        }
        if (this.modTCPinputstartAddTXT === "" || this.modTCPinputstartAddTXT === null) {
          this.warningMessage("Please enter a mod tcp input register start address");
          this.$router.replace({ path: '/dcu/upstreamconfig' });
          return false;
        }
        if (this.modTCPDiscriteinputstartAddTXT === "" || this.modTCPDiscriteinputstartAddTXT === null) {
          this.warningMessage("Please enter a mod tcp discrite input start address");
          this.$router.replace({ path: '/dcu/upstreamconfig' });
          return false;
        }
      }

      if (this.mqttEnablecheckbox) {
        if (this.mqttBrokerIpTXT === "" || this.mqttBrokerIpTXT === null) {
          this.warningMessage("Please enter a mqtt ip address");
          this.$router.replace({ path: '/dcu/upstreamconfig' });
          return false;
        }
        var bool22 = this.ValidateIPaddress(this.mqttBrokerIpTXT);
        if (!bool22) {
          this.warningMessage("You have entered mqtt ip address is invalid IP address!");
          this.$router.replace({ path: '/dcu/deviceconfig' });
          return false;
        }
        if (this.mqttBrokerPortTXT === "" || this.mqttBrokerPortTXT === null) {
          this.warningMessage("Please enter a mqtt port number");
          this.$router.replace({ path: '/dcu/upstreamconfig' });
          return false;
        }
        if (this.mqttBrokerUserNameTXT === "" || this.mqttBrokerUserNameTXT === null) {
          this.warningMessage("Please enter a mqtt user name");
          this.$router.replace({ path: '/dcu/upstreamconfig' });
          return false;
        }
        if (this.mqttBrokerPasswordTXT === "" || this.mqttBrokerPasswordTXT === null) {
          this.warningMessage("Please enter a mqtt password");
          this.$router.replace({ path: '/dcu/upstreamconfig' });
          return false;
        }
        if (this.mqttBrokerCycDataTopicTXT === "" || this.mqttBrokerCycDataTopicTXT === null) {
          this.warningMessage("Please enter a mqtt cyclic data topic");
          this.$router.replace({ path: '/dcu/upstreamconfig' });
          return false;
        }
        if (this.mqttBrokerCmdTopicTXT === "" || this.mqttBrokerCmdTopicTXT === null) {
          this.warningMessage("Please enter a mqtt cmd topic");
          this.$router.replace({ path: '/dcu/upstreamconfig' });
          return false;
        }
        if (this.mqttEnableEventTopicTXT) {
          if (this.mqttEventTopicTXT === "" || this.mqttEventTopicTXT === null) {
            this.warningMessage("Please enter a mqtt event topic");
            this.$router.replace({ path: '/dcu/upstreamconfig' });
            return false;
          }
        }
        if (this.mqttEnableDiagTopicTXT) {
          if (this.mqttDiagTopicTXT === "" || this.mqttDiagTopicTXT === null) {
            this.warningMessage("Please enter a mqtt diag topic");
            this.$router.replace({ path: '/dcu/upstreamconfig' });
            return false;
          }
        }
        if (this.mqttPeriodTXT === "" || this.mqttPeriodTXT === null) {
          this.warningMessage("Please enter a mqtt cycic peroid");
          this.$router.replace({ path: '/dcu/upstreamconfig' });
          return false;
        }
      }
      if (this.cmsEMSEnablecheckbox) {
        if (this.cmsemsEnableIPTXT === "" || this.cmsemsEnableIPTXT === null) {
          this.warningMessage("Please enter a cms rms ip address");
          this.$router.replace({ path: '/dcu/upstreamconfig' });
          return false;
        }
        var bool22 = this.ValidateIPaddress(this.cmsemsEnableIPTXT);
        if (!bool22) {
          this.warningMessage("You have entered cms rms ip address is invalid IP address!");
          this.$router.replace({ path: '/dcu/deviceconfig' });
          return false;
        }
        if (this.cmsemsEnableportNoTXT === "" || this.cmsemsEnableportNoTXT === null) {
          this.warningMessage("Please enter a cms rms port number");
          this.$router.replace({ path: '/dcu/upstreamconfig' });
          return false;
        }
        if (this.cmsemsPeriodTXT === "" || this.cmsemsPeriodTXT === null) {
          this.warningMessage("Please enter a cms rms peroid");
          this.$router.replace({ path: '/dcu/upstreamconfig' });
          return false;
        }
      }
    },
    upStreampageLoad: function upStreampageLoad() {
      this.iec104Enablechekbox = this.upStreamCONFIGPageJSON.DATA.UpstreamDataCfg.IEC104Supp == 'No' ? false : true;
      this.iecStationTXT = this.upStreamCONFIGPageJSON.DATA.IEC104Cfg.StationAddr;
      this.iecportTXT = this.upStreamCONFIGPageJSON.DATA.IEC104Cfg.PortNo;
      this.startIOAaddTXT = this.upStreamCONFIGPageJSON.DATA.IEC104Cfg.MetStartIoa;
      this.iecCylicTXT = this.upStreamCONFIGPageJSON.DATA.IEC104Cfg.CycInt;
      this.iecIOAsizedwnTXT = this.upStreamCONFIGPageJSON.DATA.IEC104Cfg.IoaSize;
      this.iecCodsizedwnTXT = this.upStreamCONFIGPageJSON.DATA.IEC104Cfg.CotSize;

      this.allowMastercheckbox = this.deviceCONFIGPageJSON.DATA.AllowedMasterCfg.EnableAllowMaster == 'No' ? false : true;
      this.allowMastercheckbox1 = this.deviceCONFIGPageJSON.DATA.AllowedMasterCfg.AllowedMasterList[0].Enable == 'No' ? false : true;
      this.allowMasterTXT1 = this.deviceCONFIGPageJSON.DATA.AllowedMasterCfg.AllowedMasterList[0].Ip;
      this.allowMastercheckbox2 = this.deviceCONFIGPageJSON.DATA.AllowedMasterCfg.AllowedMasterList[1].Enable == 'No' ? false : true;
      this.allowMasterTXT2 = this.deviceCONFIGPageJSON.DATA.AllowedMasterCfg.AllowedMasterList[1].Ip;
      this.allowMastercheckbox3 = this.deviceCONFIGPageJSON.DATA.AllowedMasterCfg.AllowedMasterList[2].Enable == 'No' ? false : true;
      this.allowMasterTXT3 = this.deviceCONFIGPageJSON.DATA.AllowedMasterCfg.AllowedMasterList[2].Ip;
      this.allowMastercheckbox4 = this.deviceCONFIGPageJSON.DATA.AllowedMasterCfg.AllowedMasterList[3].Enable == 'No' ? false : true;
      this.allowMasterTXT4 = this.deviceCONFIGPageJSON.DATA.AllowedMasterCfg.AllowedMasterList[3].Ip;

      this.ftpEnablechekbox = this.upStreamCONFIGPageJSON.DATA.UpstreamDataCfg.FtpPushSupp == 'No' ? false : true;
      this.ftpIpaddTXT = this.upStreamCONFIGPageJSON.DATA.FtpServerCfg.ServerIp;
      this.ftpprtnoTXT = this.upStreamCONFIGPageJSON.DATA.FtpServerCfg.PortNo;
      this.ftpusernameTXT = this.upStreamCONFIGPageJSON.DATA.FtpServerCfg.UserName;
      this.ftppasswordTXT = this.upStreamCONFIGPageJSON.DATA.FtpServerCfg.Password;
      this.ftpdirTXT = this.upStreamCONFIGPageJSON.DATA.FtpServerCfg.RemoteDir;
      this.ftptimeoutTXT = this.upStreamCONFIGPageJSON.DATA.FtpServerCfg.UploadPeriod;
      this.ftpLOGEnablechekbox = this.upStreamCONFIGPageJSON.DATA.FtpServerCfg.DiffServerForLogs == 'No' ? false : true;
      this.ftpLOGIpaddTXT = this.upStreamCONFIGPageJSON.DATA.FtpServerCfg.LogServerIp;
      this.ftpLOGprtnoTXT = this.upStreamCONFIGPageJSON.DATA.FtpServerCfg.LogPortNo;
      this.ftpLOGusernameTXT = this.upStreamCONFIGPageJSON.DATA.FtpServerCfg.LogUserName;
      this.ftpLOGpasswordTXT = this.upStreamCONFIGPageJSON.DATA.FtpServerCfg.LogPassword;
      this.ftpLOGdirTXT = this.upStreamCONFIGPageJSON.DATA.FtpServerCfg.LogRemoteDir;
      this.ftpLOGtimeoutTXT = this.upStreamCONFIGPageJSON.DATA.FtpServerCfg.LogUploadPeriod;

      this.modTcpEnablechekbox = this.upStreamCONFIGPageJSON.DATA.UpstreamDataCfg.ModTcpSupp == 'No' ? false : true;
      this.modTCPdeVidTXT = this.upStreamCONFIGPageJSON.DATA.ModTcpCfg.ModDevId;
      this.RespToAllSlaveIdTXT = this.upStreamCONFIGPageJSON.DATA.ModTcpCfg.RespToAllSlaveId;
      this.modTCPprtnoTXT = this.upStreamCONFIGPageJSON.DATA.ModTcpCfg.PortNo;
      this.modTCPholdstartAddTXT = this.upStreamCONFIGPageJSON.DATA.ModTcpCfg.HoldRegStartAddr;
      this.modTCPinputstartAddTXT = this.upStreamCONFIGPageJSON.DATA.ModTcpCfg.InputRegStartAddr;
      this.modTCPDiscriteinputstartAddTXT = this.upStreamCONFIGPageJSON.DATA.ModTcpCfg.ReadDiscriteInputStartAddr;

      this.mqttEnablecheckbox = this.upStreamCONFIGPageJSON.DATA.UpstreamDataCfg.MQTTSupp == 'No' ? false : true;
      this.mqttBrokerIpTXT = this.upStreamCONFIGPageJSON.DATA.MQTTCfg.BrokerIp;
      this.mqttBrokerPortTXT = this.upStreamCONFIGPageJSON.DATA.MQTTCfg.PortNo;
      this.mqttBrokerUserNameTXT = this.upStreamCONFIGPageJSON.DATA.MQTTCfg.UserName;
      this.mqttBrokerPasswordTXT = this.upStreamCONFIGPageJSON.DATA.MQTTCfg.Password;
      this.mqttBrokerCycDataTopicTXT = this.upStreamCONFIGPageJSON.DATA.MQTTCfg.CycDataTopic;
      this.mqttBrokerCmdTopicTXT = this.upStreamCONFIGPageJSON.DATA.MQTTCfg.CmdTopic;
      this.mqttEnableEventTopicTXT = this.upStreamCONFIGPageJSON.DATA.MQTTCfg.EnableEventTopic == 'No' ? false : true;
      this.mqttEventTopicTXT = this.upStreamCONFIGPageJSON.DATA.MQTTCfg.EventTopic;
      this.mqttEnableDiagTopicTXT = this.upStreamCONFIGPageJSON.DATA.MQTTCfg.EnableDiagTopic == 'No' ? false : true;
      this.mqttDiagTopicTXT = this.upStreamCONFIGPageJSON.DATA.MQTTCfg.DiagTopic;
      this.mqttPeriodTXT = this.upStreamCONFIGPageJSON.DATA.MQTTCfg.CycPeriod;

      this.cmsEMSEnablecheckbox = this.upStreamCONFIGPageJSON.DATA.UpstreamDataCfg.CMSEMSSupp == 'No' ? false : true;
      this.cmsemsEnableIPTXT = this.upStreamCONFIGPageJSON.DATA.CMSEMSCfg.BrokerIp;
      this.cmsemsEnableportNoTXT = this.upStreamCONFIGPageJSON.DATA.CMSEMSCfg.PortNo;
      this.cmsemsEnableEvent = this.upStreamCONFIGPageJSON.DATA.CMSEMSCfg.EnableEvent == 'No' ? false : true;
      this.cmsemsEnableDiag = this.upStreamCONFIGPageJSON.DATA.CMSEMSCfg.EnableDiag == 'No' ? false : true;
      this.cmsemsPeriodTXT = this.upStreamCONFIGPageJSON.DATA.CMSEMSCfg.CycPeriod;
    },
    saveUpstremConfig: function saveUpstremConfig() {
      this.upStreamCONFIGPageJSON.DATA.UpstreamDataCfg.IEC104Supp = this.iec104Enablechekbox == true ? "Yes" : "No";
      this.upStreamCONFIGPageJSON.DATA.IEC104Cfg.StationAddr = this.iecStationTXT;
      this.upStreamCONFIGPageJSON.DATA.IEC104Cfg.MetStartIoa = this.startIOAaddTXT;
      this.upStreamCONFIGPageJSON.DATA.IEC104Cfg.CycInt = this.iecCylicTXT;
      this.upStreamCONFIGPageJSON.DATA.IEC104Cfg.PortNo = this.iecportTXT;
      this.upStreamCONFIGPageJSON.DATA.IEC104Cfg.IoaSize = this.iecIOAsizedwnTXT;
      this.upStreamCONFIGPageJSON.DATA.IEC104Cfg.CotSize = this.iecCodsizedwnTXT;

      this.deviceCONFIGPageJSON.DATA.AllowedMasterCfg.EnableAllowMaster = this.allowMastercheckbox == true ? "Yes" : "No";
      this.deviceCONFIGPageJSON.DATA.AllowedMasterCfg.AllowedMasterList[0].Enable = this.allowMastercheckbox1 == true ? "Yes" : "No";
      this.deviceCONFIGPageJSON.DATA.AllowedMasterCfg.AllowedMasterList[0].Ip = this.allowMasterTXT1;
      this.deviceCONFIGPageJSON.DATA.AllowedMasterCfg.AllowedMasterList[1].Enable = this.allowMastercheckbox2 == true ? "Yes" : "No";
      this.deviceCONFIGPageJSON.DATA.AllowedMasterCfg.AllowedMasterList[1].Ip = this.allowMasterTXT2;
      this.deviceCONFIGPageJSON.DATA.AllowedMasterCfg.AllowedMasterList[2].Enable = this.allowMastercheckbox3 == true ? "Yes" : "No";
      this.deviceCONFIGPageJSON.DATA.AllowedMasterCfg.AllowedMasterList[2].Ip = this.allowMasterTXT3;
      this.deviceCONFIGPageJSON.DATA.AllowedMasterCfg.AllowedMasterList[3].Enable = this.allowMastercheckbox4 == true ? "Yes" : "No";
      this.deviceCONFIGPageJSON.DATA.AllowedMasterCfg.AllowedMasterList[3].Ip = this.allowMasterTXT4;

      this.upStreamCONFIGPageJSON.DATA.UpstreamDataCfg.FtpPushSupp = this.ftpEnablechekbox == true ? "Yes" : "No";
      this.upStreamCONFIGPageJSON.DATA.FtpServerCfg.ServerIp = this.ftpIpaddTXT;
      this.upStreamCONFIGPageJSON.DATA.FtpServerCfg.PortNo = this.ftpprtnoTXT;
      this.upStreamCONFIGPageJSON.DATA.FtpServerCfg.UserName = this.ftpusernameTXT;
      this.upStreamCONFIGPageJSON.DATA.FtpServerCfg.Password = this.ftppasswordTXT;
      this.upStreamCONFIGPageJSON.DATA.FtpServerCfg.RemoteDir = this.ftpdirTXT;
      this.upStreamCONFIGPageJSON.DATA.FtpServerCfg.UploadPeriod = this.ftptimeoutTXT;
      this.upStreamCONFIGPageJSON.DATA.FtpServerCfg.DiffServerForLogs = this.ftpLOGEnablechekbox == true ? "Yes" : "No";
      this.upStreamCONFIGPageJSON.DATA.FtpServerCfg.LogServerIp = this.ftpLOGIpaddTXT;
      this.upStreamCONFIGPageJSON.DATA.FtpServerCfg.LogPortNo = this.ftpLOGprtnoTXT;
      this.upStreamCONFIGPageJSON.DATA.FtpServerCfg.LogUserName = this.ftpLOGusernameTXT;
      this.upStreamCONFIGPageJSON.DATA.FtpServerCfg.LogPassword = this.ftpLOGpasswordTXT;
      this.upStreamCONFIGPageJSON.DATA.FtpServerCfg.LogRemoteDir = this.ftpLOGdirTXT;
      this.upStreamCONFIGPageJSON.DATA.FtpServerCfg.LogUploadPeriod = this.ftpLOGtimeoutTXT;

      this.upStreamCONFIGPageJSON.DATA.UpstreamDataCfg.ModTcpSupp = this.modTcpEnablechekbox == true ? "Yes" : "No";
      this.upStreamCONFIGPageJSON.DATA.ModTcpCfg.ModDevId = this.modTCPdeVidTXT;
      this.upStreamCONFIGPageJSON.DATA.ModTcpCfg.RespToAllSlaveId = this.RespToAllSlaveIdTXT;
      this.upStreamCONFIGPageJSON.DATA.ModTcpCfg.PortNo = this.modTCPprtnoTXT;
      this.upStreamCONFIGPageJSON.DATA.ModTcpCfg.HoldRegStartAddr = this.modTCPholdstartAddTXT;
      this.upStreamCONFIGPageJSON.DATA.ModTcpCfg.InputRegStartAddr = this.modTCPinputstartAddTXT;
      this.upStreamCONFIGPageJSON.DATA.ModTcpCfg.ReadDiscriteInputStartAddr = this.modTCPDiscriteinputstartAddTXT;

      this.upStreamCONFIGPageJSON.DATA.UpstreamDataCfg.MQTTSupp = this.mqttEnablecheckbox == true ? "Yes" : "No";
      this.upStreamCONFIGPageJSON.DATA.MQTTCfg.BrokerIp = this.mqttBrokerIpTXT;
      this.upStreamCONFIGPageJSON.DATA.MQTTCfg.PortNo = this.mqttBrokerPortTXT;
      this.upStreamCONFIGPageJSON.DATA.MQTTCfg.UserName = this.mqttBrokerUserNameTXT;
      this.upStreamCONFIGPageJSON.DATA.MQTTCfg.Password = this.mqttBrokerPasswordTXT;
      this.upStreamCONFIGPageJSON.DATA.MQTTCfg.CycDataTopic = this.mqttBrokerCycDataTopicTXT;
      this.upStreamCONFIGPageJSON.DATA.MQTTCfg.CmdTopic = this.mqttBrokerCmdTopicTXT;
      this.upStreamCONFIGPageJSON.DATA.MQTTCfg.EnableEventTopic = this.mqttEnableEventTopicTXT == true ? "Yes" : "No";
      this.upStreamCONFIGPageJSON.DATA.MQTTCfg.EventTopic = this.mqttEventTopicTXT;
      this.upStreamCONFIGPageJSON.DATA.MQTTCfg.EnableDiagTopic = this.mqttEnableDiagTopicTXT == true ? "Yes" : "No";
      this.upStreamCONFIGPageJSON.DATA.MQTTCfg.DiagTopic = this.mqttDiagTopicTXT;
      this.upStreamCONFIGPageJSON.DATA.MQTTCfg.CycPeriod = this.mqttPeriodTXT;

      this.upStreamCONFIGPageJSON.DATA.UpstreamDataCfg.CMSEMSSupp = this.cmsEMSEnablecheckbox == true ? "Yes" : "No";
      this.upStreamCONFIGPageJSON.DATA.CMSEMSCfg.BrokerIp = this.cmsemsEnableIPTXT;
      this.upStreamCONFIGPageJSON.DATA.CMSEMSCfg.PortNo = this.cmsemsEnableportNoTXT;
      this.upStreamCONFIGPageJSON.DATA.CMSEMSCfg.EnableEvent = this.cmsemsEnableEvent == true ? "Yes" : "No";
      this.upStreamCONFIGPageJSON.DATA.CMSEMSCfg.EnableDiag = this.cmsemsEnableDiag == true ? "Yes" : "No";
      this.upStreamCONFIGPageJSON.DATA.CMSEMSCfg.CycPeriod = this.cmsemsPeriodTXT;

      this.$session.set('get_GenconfigJSON', this.deviceCONFIGPageJSON);
      this.$session.set('get_UpstreamconfigJSON', this.upStreamCONFIGPageJSON);
    },
    isNumber: function isNumber() {
      var event = event ? true : window.event;
      var charCode = event.which ? event.which : event.keyCode;
      if (charCode > 31 && (charCode < 48 || charCode > 57) && charCode !== 46) {
        event.preventDefault();
      } else {
        return true;
      }
    },
    ValidateIPaddress: function ValidateIPaddress(inputText) {
      var ipformat = /^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/;
      if (inputText.match(ipformat)) {
        return true;
      } else {

        return false;
      }
    },
    successMessage: function successMessage(msg) {
      this.$notice.success({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    warningMessage: function warningMessage(msg) {
      this.$notice.warning({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    infoMessage: function infoMessage(msg) {
      this.$notice.info({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    errorMessage: function errorMessage(msg) {
      this.$notice.error({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    }
  }
});

/***/ }),
/* 52 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
Object.defineProperty(__webpack_exports__, "__esModule", { value: true });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_crip_vue_notice__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_crip_vue_notice___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_0_crip_vue_notice__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_vue_element_loading__ = __webpack_require__(2);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_vue_element_loading___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_1_vue_element_loading__);




/* harmony default export */ __webpack_exports__["default"] = ({
  name: 'Changepass',
  components: {
    CripNotice: __WEBPACK_IMPORTED_MODULE_0_crip_vue_notice___default.a,
    VueElementLoading: __WEBPACK_IMPORTED_MODULE_1_vue_element_loading___default.a
  },
  data: function data() {
    return {
      isLoading: false,
      viewdataMeterLocTXT: 'Choose Meter Location',
      viewdataMeterDataTypeTXT: 'Choose Data Type',
      viewDataTableheight: 0,
      viewDataconfigJson: { details: [{ id: 1, date: '13-08-2020', view: '', download: '' }, { id: 2, date: '12-08-2020', view: '', download: '' }, { id: 3, date: '11-08-2020', view: '', download: '' }, { id: 4, date: '10-08-2020', view: '', download: '' }, { id: 5, date: '09-08-2020', view: '', download: '' }, { id: 6, date: '08-08-2020', view: '', download: '' }, { id: 7, date: '07-08-2020', view: '', download: '' }, { id: 8, date: '06-08-2020', view: '', download: '' }, { id: 9, date: '05-08-2020', view: '', download: '' }, { id: 10, date: '04-08-2020', view: '', download: '' }, { id: 11, date: '03-08-2020', view: '', download: '' }, { id: 12, date: '02-08-2020', view: '', download: '' }, { id: 13, date: '01-08-2020', view: '', download: '' }, { id: 14, date: '30-07-2020', view: '', download: '' }] }
    };
  },
  created: function created() {
    if (this.$session.get("loginsession") == "") {
      this.$router.replace({ path: '/' });
      return false;
    }
  },
  mounted: function mounted() {
    var _this = this;

    this.isLoading = true;
    var innerMinHeight = window.innerHeight - 125 + 'px';
    this.viewDataTableheight = window.innerHeight - 350 + 'px';
    document.getElementById('viewDATAPage').style.minHeight = innerMinHeight;
    setTimeout(function () {
      return _this.isLoading = false;
    }, 500);
  },

  methods: {
    viewDATA: function viewDATA() {
      var _this2 = this;

      this.isLoading = true;
      setTimeout(function () {
        return _this2.isLoading = false;
      }, 1000);
    },
    downloadDATA: function downloadDATA() {
      var _this3 = this;

      this.isLoading = true;
      setTimeout(function () {
        return _this3.isLoading = false;
      }, 1000);
    },

    isNumber: function isNumber(evt) {
      evt = evt ? true : window.event;
      var charCode = evt.which ? evt.which : evt.keyCode;
      if (charCode > 31 && (charCode < 48 || charCode > 57) && charCode !== 46) {
        evt.preventDefault();
      } else {
        return true;
      }
    },
    successMessage: function successMessage(msg) {
      this.$notice.success({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    warningMessage: function warningMessage(msg) {
      this.$notice.warning({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    infoMessage: function infoMessage(msg) {
      this.$notice.info({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    },
    errorMessage: function errorMessage(msg) {
      this.$notice.error({
        title: 'Notification',
        description: msg,
        duration: 3,
        onClose: function onClose() {}
      });
    }
  }
});

/***/ }),
/* 53 */,
/* 54 */,
/* 55 */,
/* 56 */,
/* 57 */,
/* 58 */,
/* 59 */,
/* 60 */,
/* 61 */,
/* 62 */,
/* 63 */,
/* 64 */,
/* 65 */,
/* 66 */,
/* 67 */,
/* 68 */,
/* 69 */
/***/ (function(module, exports) {

// removed by extract-text-webpack-plugin

/***/ }),
/* 70 */
/***/ (function(module, exports) {

// removed by extract-text-webpack-plugin

/***/ }),
/* 71 */
/***/ (function(module, exports) {

// removed by extract-text-webpack-plugin

/***/ }),
/* 72 */
/***/ (function(module, exports) {

// removed by extract-text-webpack-plugin

/***/ }),
/* 73 */
/***/ (function(module, exports) {

// removed by extract-text-webpack-plugin

/***/ }),
/* 74 */
/***/ (function(module, exports) {

// removed by extract-text-webpack-plugin

/***/ }),
/* 75 */
/***/ (function(module, exports) {

// removed by extract-text-webpack-plugin

/***/ }),
/* 76 */
/***/ (function(module, exports) {

// removed by extract-text-webpack-plugin

/***/ }),
/* 77 */
/***/ (function(module, exports) {

// removed by extract-text-webpack-plugin

/***/ }),
/* 78 */
/***/ (function(module, exports) {

// removed by extract-text-webpack-plugin

/***/ }),
/* 79 */
/***/ (function(module, exports) {

// removed by extract-text-webpack-plugin

/***/ }),
/* 80 */
/***/ (function(module, exports) {

// removed by extract-text-webpack-plugin

/***/ }),
/* 81 */
/***/ (function(module, exports) {

// removed by extract-text-webpack-plugin

/***/ }),
/* 82 */
/***/ (function(module, exports) {

// removed by extract-text-webpack-plugin

/***/ }),
/* 83 */
/***/ (function(module, exports) {

// removed by extract-text-webpack-plugin

/***/ }),
/* 84 */
/***/ (function(module, exports) {

// removed by extract-text-webpack-plugin

/***/ }),
/* 85 */
/***/ (function(module, exports) {

// removed by extract-text-webpack-plugin

/***/ }),
/* 86 */
/***/ (function(module, exports) {

// removed by extract-text-webpack-plugin

/***/ }),
/* 87 */
/***/ (function(module, exports) {

// removed by extract-text-webpack-plugin

/***/ }),
/* 88 */
/***/ (function(module, exports) {

// removed by extract-text-webpack-plugin

/***/ }),
/* 89 */
/***/ (function(module, exports) {

// removed by extract-text-webpack-plugin

/***/ }),
/* 90 */,
/* 91 */,
/* 92 */
/***/ (function(module, exports, __webpack_require__) {


/* styles */
__webpack_require__(89)

var Component = __webpack_require__(0)(
  /* script */
  __webpack_require__(29),
  /* template */
  __webpack_require__(140),
  /* scopeId */
  null,
  /* cssModules */
  null
)

module.exports = Component.exports


/***/ }),
/* 93 */
/***/ (function(module, exports, __webpack_require__) {


/* styles */
__webpack_require__(70)

var Component = __webpack_require__(0)(
  /* script */
  __webpack_require__(30),
  /* template */
  __webpack_require__(118),
  /* scopeId */
  "data-v-1aa3afbc",
  /* cssModules */
  null
)

module.exports = Component.exports


/***/ }),
/* 94 */
/***/ (function(module, exports, __webpack_require__) {


/* styles */
__webpack_require__(76)

var Component = __webpack_require__(0)(
  /* script */
  __webpack_require__(31),
  /* template */
  __webpack_require__(126),
  /* scopeId */
  "data-v-3c14a2cb",
  /* cssModules */
  null
)

module.exports = Component.exports


/***/ }),
/* 95 */
/***/ (function(module, exports, __webpack_require__) {

var Component = __webpack_require__(0)(
  /* script */
  __webpack_require__(32),
  /* template */
  __webpack_require__(133),
  /* scopeId */
  null,
  /* cssModules */
  null
)

module.exports = Component.exports


/***/ }),
/* 96 */
/***/ (function(module, exports, __webpack_require__) {


/* styles */
__webpack_require__(71)

var Component = __webpack_require__(0)(
  /* script */
  __webpack_require__(33),
  /* template */
  __webpack_require__(119),
  /* scopeId */
  "data-v-2649b32c",
  /* cssModules */
  null
)

module.exports = Component.exports


/***/ }),
/* 97 */
/***/ (function(module, exports, __webpack_require__) {

var Component = __webpack_require__(0)(
  /* script */
  __webpack_require__(34),
  /* template */
  __webpack_require__(120),
  /* scopeId */
  null,
  /* cssModules */
  null
)

module.exports = Component.exports


/***/ }),
/* 98 */
/***/ (function(module, exports, __webpack_require__) {


/* styles */
__webpack_require__(77)

var Component = __webpack_require__(0)(
  /* script */
  __webpack_require__(35),
  /* template */
  __webpack_require__(127),
  /* scopeId */
  "data-v-3c167c9c",
  /* cssModules */
  null
)

module.exports = Component.exports


/***/ }),
/* 99 */
/***/ (function(module, exports, __webpack_require__) {


/* styles */
__webpack_require__(85)

var Component = __webpack_require__(0)(
  /* script */
  __webpack_require__(36),
  /* template */
  __webpack_require__(136),
  /* scopeId */
  "data-v-67bbc04e",
  /* cssModules */
  null
)

module.exports = Component.exports


/***/ }),
/* 100 */
/***/ (function(module, exports, __webpack_require__) {


/* styles */
__webpack_require__(82)

var Component = __webpack_require__(0)(
  /* script */
  __webpack_require__(37),
  /* template */
  __webpack_require__(132),
  /* scopeId */
  null,
  /* cssModules */
  null
)

module.exports = Component.exports


/***/ }),
/* 101 */
/***/ (function(module, exports, __webpack_require__) {


/* styles */
__webpack_require__(81)

var Component = __webpack_require__(0)(
  /* script */
  __webpack_require__(38),
  /* template */
  __webpack_require__(131),
  /* scopeId */
  null,
  /* cssModules */
  null
)

module.exports = Component.exports


/***/ }),
/* 102 */
/***/ (function(module, exports, __webpack_require__) {

var Component = __webpack_require__(0)(
  /* script */
  __webpack_require__(39),
  /* template */
  __webpack_require__(117),
  /* scopeId */
  null,
  /* cssModules */
  null
)

module.exports = Component.exports


/***/ }),
/* 103 */
/***/ (function(module, exports, __webpack_require__) {

var Component = __webpack_require__(0)(
  /* script */
  __webpack_require__(40),
  /* template */
  __webpack_require__(124),
  /* scopeId */
  null,
  /* cssModules */
  null
)

module.exports = Component.exports


/***/ }),
/* 104 */
/***/ (function(module, exports, __webpack_require__) {


/* styles */
__webpack_require__(79)

var Component = __webpack_require__(0)(
  /* script */
  __webpack_require__(41),
  /* template */
  __webpack_require__(129),
  /* scopeId */
  null,
  /* cssModules */
  null
)

module.exports = Component.exports


/***/ }),
/* 105 */
/***/ (function(module, exports, __webpack_require__) {


/* styles */
__webpack_require__(75)

var Component = __webpack_require__(0)(
  /* script */
  __webpack_require__(42),
  /* template */
  __webpack_require__(125),
  /* scopeId */
  null,
  /* cssModules */
  null
)

module.exports = Component.exports


/***/ }),
/* 106 */
/***/ (function(module, exports, __webpack_require__) {


/* styles */
__webpack_require__(74)

var Component = __webpack_require__(0)(
  /* script */
  __webpack_require__(43),
  /* template */
  __webpack_require__(123),
  /* scopeId */
  null,
  /* cssModules */
  null
)

module.exports = Component.exports


/***/ }),
/* 107 */
/***/ (function(module, exports, __webpack_require__) {


/* styles */
__webpack_require__(87)

var Component = __webpack_require__(0)(
  /* script */
  __webpack_require__(44),
  /* template */
  __webpack_require__(138),
  /* scopeId */
  null,
  /* cssModules */
  null
)

module.exports = Component.exports


/***/ }),
/* 108 */
/***/ (function(module, exports, __webpack_require__) {


/* styles */
__webpack_require__(86)

var Component = __webpack_require__(0)(
  /* script */
  __webpack_require__(45),
  /* template */
  __webpack_require__(137),
  /* scopeId */
  null,
  /* cssModules */
  null
)

module.exports = Component.exports


/***/ }),
/* 109 */
/***/ (function(module, exports, __webpack_require__) {


/* styles */
__webpack_require__(80)

var Component = __webpack_require__(0)(
  /* script */
  __webpack_require__(46),
  /* template */
  __webpack_require__(130),
  /* scopeId */
  null,
  /* cssModules */
  null
)

module.exports = Component.exports


/***/ }),
/* 110 */
/***/ (function(module, exports, __webpack_require__) {


/* styles */
__webpack_require__(72)

var Component = __webpack_require__(0)(
  /* script */
  __webpack_require__(47),
  /* template */
  __webpack_require__(121),
  /* scopeId */
  "data-v-31914d28",
  /* cssModules */
  null
)

module.exports = Component.exports


/***/ }),
/* 111 */
/***/ (function(module, exports, __webpack_require__) {


/* styles */
__webpack_require__(78)

var Component = __webpack_require__(0)(
  /* script */
  __webpack_require__(48),
  /* template */
  __webpack_require__(128),
  /* scopeId */
  null,
  /* cssModules */
  null
)

module.exports = Component.exports


/***/ }),
/* 112 */
/***/ (function(module, exports, __webpack_require__) {


/* styles */
__webpack_require__(83)

var Component = __webpack_require__(0)(
  /* script */
  __webpack_require__(49),
  /* template */
  __webpack_require__(134),
  /* scopeId */
  null,
  /* cssModules */
  null
)

module.exports = Component.exports


/***/ }),
/* 113 */
/***/ (function(module, exports, __webpack_require__) {


/* styles */
__webpack_require__(73)

var Component = __webpack_require__(0)(
  /* script */
  __webpack_require__(50),
  /* template */
  __webpack_require__(122),
  /* scopeId */
  null,
  /* cssModules */
  null
)

module.exports = Component.exports


/***/ }),
/* 114 */
/***/ (function(module, exports, __webpack_require__) {


/* styles */
__webpack_require__(88)

var Component = __webpack_require__(0)(
  /* script */
  __webpack_require__(51),
  /* template */
  __webpack_require__(139),
  /* scopeId */
  null,
  /* cssModules */
  null
)

module.exports = Component.exports


/***/ }),
/* 115 */
/***/ (function(module, exports, __webpack_require__) {


/* styles */
__webpack_require__(84)

var Component = __webpack_require__(0)(
  /* script */
  __webpack_require__(52),
  /* template */
  __webpack_require__(135),
  /* scopeId */
  null,
  /* cssModules */
  null
)

module.exports = Component.exports


/***/ }),
/* 116 */
/***/ (function(module, exports) {

module.exports={render:function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('div', {
    attrs: {
      "id": "app"
    }
  }, [_c('router-view')], 1)
},staticRenderFns: []}

/***/ }),
/* 117 */
/***/ (function(module, exports) {

module.exports={render:function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('li', {
    staticClass: "dropdown tasks-menu"
  }, [_c('a', {
    staticClass: "dropdown-toggle",
    attrs: {
      "href": "javascript:;",
      "data-toggle": "dropdown"
    }
  }, [_c('i', {
    staticClass: "fa fa-flag-o"
  }), _vm._v(" "), _c('span', {
    staticClass: "label label-danger"
  }, [_vm._v(_vm._s(_vm._f("count")(_vm.userInfo.tasks)) + " ")])]), _vm._v(" "), _c('ul', {
    staticClass: "dropdown-menu"
  }, [_c('li', {
    staticClass: "header"
  }, [_vm._v("You have " + _vm._s(_vm._f("count")(_vm.userInfo.tasks)) + " task(s)")]), _vm._v(" "), (_vm.userInfo.tasks.length > 0) ? _c('li', [_vm._m(0)]) : _vm._e(), _vm._v(" "), (_vm.userInfo.tasks.length > 0) ? _c('li', {
    staticClass: "footer"
  }, [_c('a', {
    attrs: {
      "href": "javascript:;"
    }
  }, [_vm._v("View all tasks")])]) : _vm._e()])])
},staticRenderFns: [function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('ul', {
    staticClass: "menu"
  }, [_c('li', [_c('a', {
    attrs: {
      "href": "javascript:;"
    }
  }, [_c('h3', [_vm._v("\n              Design some buttons\n              "), _c('small', {
    staticClass: "pull-right"
  }, [_vm._v("20%")])]), _vm._v(" "), _c('div', {
    staticClass: "progress xs"
  }, [_c('div', {
    staticClass: "progress-bar progress-bar-aqua",
    staticStyle: {
      "width": "20%"
    },
    attrs: {
      "role": "progressbar",
      "aria-valuenow": "20",
      "aria-valuemin": "0",
      "aria-valuemax": "100"
    }
  }, [_c('span', {
    staticClass: "sr-only"
  }, [_vm._v("20% Complete")])])])])])])
}]}

/***/ }),
/* 118 */
/***/ (function(module, exports) {

module.exports={render:function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('div', {
    attrs: {
      "id": "loginpage"
    }
  }, [_c('vue-element-loading', {
    attrs: {
      "active": _vm.isLoading,
      "spinner": "spinner",
      "color": "#000",
      "is-full-screen": true
    }
  }), _vm._v(" "), _c('div', {
    staticClass: "container-login100"
  }, [_c('div', {
    staticClass: "wrap-login100 p-l-55 p-r-55 p-t-80 p-b-30"
  }, [_c('div', {
    staticClass: "login100-form validate-form"
  }, [_vm._m(0), _vm._v(" "), _c('span', {
    staticClass: "login100-form-title p-b-37",
    staticStyle: {
      "font-size": "29px !important"
    }
  }, [_vm._v("Data Concentrator Unit")]), _vm._v(" "), _c('div', {
    staticClass: "wrap-input100 validate-input m-b-20"
  }, [_c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.ducUserNameTXT),
      expression: "ducUserNameTXT"
    }],
    staticClass: "input100",
    attrs: {
      "id": "usernameid",
      "type": "text",
      "name": "username",
      "placeholder": "username"
    },
    domProps: {
      "value": (_vm.ducUserNameTXT)
    },
    on: {
      "keyup": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "enter", 13, $event.key, "Enter")) { return null; }
        return _vm.loginAction($event)
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.ducUserNameTXT = $event.target.value
      }
    }
  }), _vm._v(" "), _c('span', {
    staticClass: "focus-input100"
  })]), _vm._v(" "), _c('div', {
    staticClass: "wrap-input100 validate-input m-b-25"
  }, [_c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.ducPasswordTXT),
      expression: "ducPasswordTXT"
    }],
    staticClass: "input100",
    attrs: {
      "id": "passid",
      "type": "password",
      "name": "pass",
      "placeholder": "password"
    },
    domProps: {
      "value": (_vm.ducPasswordTXT)
    },
    on: {
      "keyup": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "enter", 13, $event.key, "Enter")) { return null; }
        return _vm.loginAction($event)
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.ducPasswordTXT = $event.target.value
      }
    }
  }), _vm._v(" "), _c('span', {
    staticClass: "focus-input100"
  })]), _vm._v(" "), _c('div', {
    staticClass: "container-login100-form-btn"
  }, [_c('button', {
    staticClass: "login100-form-btn",
    attrs: {
      "id": "loginbtn"
    },
    on: {
      "click": _vm.loginAction
    }
  }, [_vm._v("Sign In")])]), _vm._v(" "), _c('div', {
    staticClass: "text-center p-t-57 p-b-20"
  }, [_c('span', {
    staticClass: "txt1",
    staticStyle: {
      "color": "red"
    }
  }, [_vm._v(_vm._s(_vm.responseTXT))])]), _vm._v(" "), _c('div', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (false),
      expression: "false"
    }],
    staticClass: "text-center"
  }, [_c('a', {
    staticClass: "txt2 hov1",
    attrs: {
      "href": "#"
    }
  }, [_vm._v("Forget Password?")])])])])])], 1)
},staticRenderFns: [function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('div', {
    staticClass: "login100-form-title"
  }, [_c('img', {
    attrs: {
      "src": "/static/img/images/dculogo.png",
      "width": "80"
    }
  })])
}]}

/***/ }),
/* 119 */
/***/ (function(module, exports) {

module.exports={render:function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('li', [_c('a', {
    attrs: {
      "href": "javascript:;"
    }
  }, [_c('h4', [_c('span', [_vm._v(_vm._s(_vm.message.title))]), _vm._v(" "), _c('small', [_c('i', {
    staticClass: "fa fa-clock-o"
  }), _vm._v(" "), _c('span', [_vm._v(_vm._s(_vm.message.createdAt))])])]), _vm._v(" "), _c('p', [_vm._v(_vm._s(_vm.message.body))])])])
},staticRenderFns: []}

/***/ }),
/* 120 */
/***/ (function(module, exports) {

module.exports={render:function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('li', {
    staticClass: "dropdown messages-menu"
  }, [_c('a', {
    staticClass: "dropdown-toggle",
    attrs: {
      "href": "javascript:;",
      "data-toggle": "dropdown"
    }
  }, [_c('i', {
    staticClass: "fa fa-envelope-o"
  }), _vm._v(" "), _c('span', {
    staticClass: "label label-success"
  }, [_vm._v(_vm._s(_vm._f("count")(_vm.userInfo.messages)))])]), _vm._v(" "), _c('ul', {
    staticClass: "dropdown-menu"
  }, [_c('li', {
    staticClass: "header"
  }, [_vm._v("You have " + _vm._s(_vm._f("count")(_vm.userInfo.messages)) + " message(s)")]), _vm._v(" "), (_vm.userInfo.messages.length > 0) ? _c('li', [_c('ul', {
    staticClass: "menu"
  }, _vm._l((_vm.userInfo.messages), function(message) {
    return _c('message-item', {
      key: message.id,
      attrs: {
        "message": message
      }
    })
  }), 1)]) : _vm._e(), _vm._v(" "), (_vm.userInfo.messages.length > 0) ? _c('li', {
    staticClass: "footer"
  }, [_c('a', {
    attrs: {
      "href": "javascript:;"
    }
  }, [_vm._v("See All Messages")])]) : _vm._e()])])
},staticRenderFns: []}

/***/ }),
/* 121 */
/***/ (function(module, exports) {

module.exports={render:function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('section', {
    staticClass: "content",
    attrs: {
      "id": "saveRestartPane"
    }
  }, [_c('vue-element-loading', {
    attrs: {
      "active": _vm.isLoading,
      "spinner": "spinner",
      "color": "#000",
      "is-full-screen": true
    }
  }), _vm._v(" "), _c('BlockUI', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (_vm.blockdevice),
      expression: "blockdevice"
    }],
    attrs: {
      "message": _vm.msg,
      "html": _vm.html
    }
  }, [_c('div', {
    staticClass: "checkbox-wrapper"
  }, [_c('i', {
    staticClass: "fa fa-cogs fa-spin fa-3x fa-fw",
    staticStyle: {
      "color": "#0073b7"
    }
  }), _vm._v(" "), _c('p'), _vm._v(" "), _c('p', {
    staticStyle: {
      "color": "#0073b7",
      "font-size": "15px"
    }
  }, [_vm._v("Please wait while the system saves the configuration and resets, you will be redirected after " + _vm._s(_vm.time) + " seconds. ")])])]), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-12"
  }, [_c('ul', {
    staticClass: "timeline"
  }, [_c('li', [_c('i', {
    staticClass: "fa fa-cog bg-yellow"
  }), _vm._v(" "), _c('div', {
    staticClass: "timeline-item"
  }, [_c('h3', {
    staticClass: "timeline-header"
  }, [_vm._v("General Configuration")]), _vm._v(" "), _c('div', {
    staticClass: "timeline-body"
  }, [_c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("DCU Id :   ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v("  " + _vm._s(_vm.saveDCUIdTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("DCU Location : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveDCULocTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Serial Number : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveDCUserialNumTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Enable DBG Log : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveDCUEnableDbgLogTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("DBG Log Level : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveDCUDbgLogLevelTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("DBG Log Ip : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveDCUDbgLogIpTXT))])])]), _vm._v(" "), _c('div', {
    staticStyle: {
      "height": "10px"
    }
  }), _vm._v(" "), _c('span', {
    staticClass: "timeline-header header-subtitle"
  }, [_vm._v("LAN Settings")]), _vm._v(" "), _c('div', {
    staticStyle: {
      "height": "10px"
    }
  }), _vm._v(" "), _c('div', {
    attrs: {
      "id": "saveEth1PANE"
    }
  }, [_vm._m(0), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Current IP Address : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveEth1currIPTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("New IP Address : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveEth1newIPTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Subnet Mask : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveEth1subnetIPTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Gateway : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveEth1gatewayIPTXT))])])]), _vm._v(" "), _c('div', {
    staticStyle: {
      "height": "15px"
    }
  })]), _vm._v(" "), _c('div', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (_vm.saveEthcount == '2'),
      expression: "saveEthcount == '2'"
    }],
    attrs: {
      "id": "saveEth12ANE"
    }
  }, [_vm._m(1), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Current IP Address : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveEth2currIPTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("New IP Address : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveEth2newIPTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Subnet Mask : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveEth2subnetIPTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Gateway : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveEth2gatewayIPTXT))])])]), _vm._v(" "), _c('div', {
    staticStyle: {
      "height": "15px"
    }
  })]), _vm._v(" "), _c('span', {
    staticClass: "timeline-header header-subtitle"
  }, [_vm._v("Modem Settings")]), _vm._v(" "), _c('div', {
    staticStyle: {
      "height": "10px"
    }
  }), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Enable :   ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v("  " + _vm._s(_vm.saveModemEnableTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("User Name : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveModemUsernameTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Password : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveModemPasswordTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Phone Number : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveModemPhnumTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("APN : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveModemAPNTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Enable Ping :   ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v("  " + _vm._s(_vm.saveModemEnablePingTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Number of Ping : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveModemNoPingTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Ping Interval : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveModemPingIntervalTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Ip address : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveModemPingIpaddressTXT))])])]), _vm._v(" "), _c('div', {
    staticStyle: {
      "height": "10px"
    }
  }), _vm._v(" "), _c('h5', [_c('b', [_vm._v("SMS (Reporting & Command)")]), _vm._v("                           \n               "), _c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v(" Enable :   ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v("  " + _vm._s(_vm.smsEnableTXT))])]), _vm._v(" "), _c('p'), _vm._v(" "), (_vm.saveUppstreamCONFIGpageJSON.DATA.SMSCfg.Details != undefined) ? _c('div', _vm._l((_vm.saveUppstreamCONFIGpageJSON.DATA.SMSCfg.Details), function(items, index) {
    return _c('div', {
      directives: [{
        name: "show",
        rawName: "v-show",
        value: (_vm.smsEnableTXT == 'Yes'),
        expression: "smsEnableTXT == 'Yes'"
      }],
      key: index,
      staticClass: "row"
    }, [_c('div', {
      staticClass: "col-lg-2"
    }, [_c('span', {
      staticClass: "inputTEXTLBLcss"
    }, [_vm._v("Name :   ")]), _vm._v(" "), _c('span', {
      staticClass: "inputANSWERLBLcss"
    }, [_vm._v(" " + _vm._s(items.Name))])]), _vm._v(" "), _c('div', {
      staticClass: "col-lg-2"
    }, [_c('span', {
      staticClass: "inputTEXTLBLcss"
    }, [_vm._v("Phone Number :   ")]), _vm._v(" "), _c('span', {
      staticClass: "inputANSWERLBLcss"
    }, [_vm._v(" " + _vm._s(items.Num))])]), _vm._v(" "), _c('p')])
  }), 0) : _vm._e(), _vm._v(" "), _c('div', {
    staticStyle: {
      "height": "10px"
    }
  }), _vm._v(" "), _c('span', {
    staticClass: "timeline-header header-subtitle"
  }, [_vm._v("NTP Settings")]), _vm._v(" "), _c('div', {
    staticStyle: {
      "height": "10px"
    }
  }), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Server 1 Enable :   ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v("  " + _vm._s(_vm.saveNTPserver1EnableTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Ip address1: ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveNTPserver1IPaddressTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-1"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Port1: ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveNTPserver1PortTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Server 2 Enable : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveNTPserver2EnableTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Ip address2: ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveNTPserver2IPaddressTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-1"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Port2: ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveNTPserver2PortTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Interval (In sec) : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveNTPserverIntervalTXT))])])])])])]), _vm._v(" "), _c('li', [_c('i', {
    staticClass: "fa fa-cogs bg-yellow"
  }), _vm._v(" "), _c('div', {
    staticClass: "timeline-item"
  }, [_c('h3', {
    staticClass: "timeline-header"
  }, [_vm._v("UpStream Configuration")]), _vm._v(" "), _c('div', {
    staticClass: "timeline-body"
  }, [_c('div', {
    staticStyle: {
      "height": "10px"
    }
  }), _vm._v(" "), _c('span', {
    staticClass: "timeline-header header-subtitle"
  }, [_vm._v("IEC-104 Settings")]), _vm._v(" "), _c('div', {
    staticStyle: {
      "height": "10px"
    }
  }), _vm._v(" "), _c('div', [_c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Station Address : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveICEstationAddTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Start IOA Address : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveICEstartIOAAddTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Cyclic int(in sec) : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveICEcyclicTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("COT Size : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveICEcotTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Port No : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveICEportTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("IOA Size : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveICEiotTXT))])])]), _vm._v(" "), _c('div', {
    staticStyle: {
      "height": "15px"
    }
  })]), _vm._v(" "), _c('div', [_c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Allowed Master Enable : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveAllowedEnableCheckboxTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Master Status 1 : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveAllowed1statusTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Master IP1 : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveAllowed1IPTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Master Status 2 : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveAllowed2statusTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Master IP2 : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveAllowed2IPTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Master Status 3 : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveAllowed3statusTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Master IP3 : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveAllowed3IPTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Master Status 4 : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveAllowed4statusTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Master IP4 : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveAllowed4IPTXT))])])]), _vm._v(" "), _c('div', {
    staticStyle: {
      "height": "15px"
    }
  })]), _vm._v(" "), _c('span', {
    staticClass: "timeline-header header-subtitle"
  }, [_vm._v("FTP Server Settings")]), _vm._v(" "), _c('div', {
    staticStyle: {
      "height": "10px"
    }
  }), _vm._v(" "), _c('div', [_c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Enable : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveFTPEnableTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("IP Address : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveFTPipAddTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Port No : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveFTPportnoAddTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("User Name : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveFTPusernameTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Password : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveFTPpasswordTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Directory : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveFTPdirTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Time Interval : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveFTPtimeintervalTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Server log Enable : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveFTPLOGEnableTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Log IP Address : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveFTPLOGipAddTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Log Port No : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveFTPLOGportnoAddTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Log User Name : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveFTPLOGusernameTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Log Password : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveFTPLOGpasswordTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Log Directory : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveFTPLOGdirTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Log Time Interval : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveFTPLOGtimeintervalTXT))])])]), _vm._v(" "), _c('div', {
    staticStyle: {
      "height": "15px"
    }
  })]), _vm._v(" "), _c('span', {
    staticClass: "timeline-header header-subtitle"
  }, [_vm._v("Mod TCP Settings")]), _vm._v(" "), _c('div', {
    staticStyle: {
      "height": "10px"
    }
  }), _vm._v(" "), _c('div', [_c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Mod TCP Enable : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveTCPEnableTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Modbus Device Id : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveTCPdeviceIdTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("RespToAllSlaveId : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveTCPRespToAllSlaveIdTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Port Number : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveTCPPortTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Hold Register Start Address : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveTCPholdstartAddTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Input Register Start Address : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveTCPinputstartAddTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Discrite Input Start Address : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveTCPDiscriteinputstartAddTXT))])])]), _vm._v(" "), _c('div', {
    staticStyle: {
      "height": "15px"
    }
  })]), _vm._v(" "), _c('span', {
    staticClass: "timeline-header header-subtitle"
  }, [_vm._v("MQTT Settings")]), _vm._v(" "), _c('div', {
    staticStyle: {
      "height": "10px"
    }
  }), _vm._v(" "), _c('div', [_c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("MQTT Enable : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveMQTTEnableTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Broker Ip :  ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveMQTTBrokerIpTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Port Number :  ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveMQTTPortnoTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("User Name :  ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveMQTTUserTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Password : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveMQTTPassTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Cyclic Data Topic : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveMQTTcyclicDataTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Cmd Topic :  ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveMQTTcmdtopicTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Topic Enable : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveMQTTenabletopicTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Event Topic : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveMQTTeventtopicTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Diag Enable : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveMQTTenableDiagTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Diag Topic  : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveMQTTDiagTopicTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Cyclic Period : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveMQTTCyclicPeriodTXT))])])]), _vm._v(" "), _c('div', {
    staticStyle: {
      "height": "15px"
    }
  })]), _vm._v(" "), _c('span', {
    staticClass: "timeline-header header-subtitle"
  }, [_vm._v("CMS EMS Settings")]), _vm._v(" "), _c('div', {
    staticStyle: {
      "height": "10px"
    }
  }), _vm._v(" "), _c('div', [_c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("CMS EMS Enable : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveCMSEMSEnableTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Ip Address : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveCMSEMSipTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Port No : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveCMSEMSportnoTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Enable Event : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveCMSEMSeventenableTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Enable Diag  : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveCMSEMSdiagenableTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Cyclic Period :  ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveCMSEMScyclicperoidenableTXT))])])]), _vm._v(" "), _c('div', {
    staticStyle: {
      "height": "15px"
    }
  })])])])]), _vm._v(" "), _c('li', [_c('i', {
    staticClass: "fa fa-star-half-o bg-yellow"
  }), _vm._v(" "), _c('div', {
    staticClass: "timeline-item"
  }, [_c('h3', {
    staticClass: "timeline-header"
  }, [_vm._v("Parameter Configuration")]), _vm._v(" "), _c('div', {
    staticClass: "timeline-body"
  }, [_c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-12"
  }, [_vm._m(2), _vm._v(" "), _c('div', {
    staticClass: "tab-content"
  }, [_c('div', {
    staticClass: "tab-pane active",
    attrs: {
      "role": "tabpanel",
      "aria-labelledby": "paramTab1PANE",
      "id": "paramTab1PANE"
    }
  }, [_c('p'), _vm._v(" "), _c('h4', {
    staticClass: "timeline-header",
    staticStyle: {
      "text-decoration": "underline",
      "color": "#0073b7"
    }
  }, [_vm._v(" Selected Instantaneous Params:")]), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
    staticClass: "col-lg-6"
  }, [
    [_c('div', {
      staticClass: "table-responsive",
      staticStyle: {
        "border": "1px solid lightgray"
      },
      style: ({
        height: 350 + 'px'
      }),
      attrs: {
        "id": "selectINSTparamsTablePane"
      }
    }, [_c('table', {
      staticClass: "table table-bordered table-responsive-stack",
      attrs: {
        "id": "selectINSTparamsTBl"
      }
    }, [_vm._m(3), _vm._v(" "), (_vm.saveinstselectedParamsList.length != 0) ? _c('tbody', _vm._l((_vm.saveinstselectedParamsList), function(items, iindex) {
      return _c('tr', {
        key: iindex
      }, [_c('td', [_vm._v(_vm._s(iindex + 1))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(items.obis))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(items.def))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(items.assign))])])
    }), 0) : _vm._e()]), _vm._v(" "), (_vm.saveinstselectedParamsList.length == 0) ? _c('div', {
      staticClass: "text-center text-block"
    }, [_c('span', [_vm._v("No Records Found")])]) : _vm._e()])]
  ], 2)]), _vm._v(" "), _c('div', {
    staticClass: "tab-pane",
    attrs: {
      "role": "tabpanel",
      "aria-labelledby": "paramTab2PANE",
      "id": "paramTab2PANE"
    }
  }, [_c('p'), _vm._v(" "), _c('h4', {
    staticClass: "timeline-header",
    staticStyle: {
      "text-decoration": "underline",
      "color": "#0073b7"
    }
  }, [_vm._v(" Selected Load Survey Params:")]), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
    staticClass: "col-lg-6"
  }, [
    [_c('div', {
      staticClass: "table-responsive",
      staticStyle: {
        "border": "1px solid lightgray"
      },
      style: ({
        height: 350 + 'px'
      }),
      attrs: {
        "id": "selectLSparamsTablePane"
      }
    }, [_c('table', {
      staticClass: "table table-bordered table-responsive-stack",
      attrs: {
        "id": "selectLSparamsTBl"
      }
    }, [_vm._m(4), _vm._v(" "), (_vm.saveloadserveselectedParamsList.length != 0) ? _c('tbody', _vm._l((_vm.saveloadserveselectedParamsList), function(items, iindex) {
      return _c('tr', {
        key: iindex
      }, [_c('td', [_vm._v(_vm._s(iindex + 1))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(items.obis))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(items.def))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(items.assign))])])
    }), 0) : _vm._e()]), _vm._v(" "), (_vm.saveloadserveselectedParamsList.length == 0) ? _c('div', {
      staticClass: "text-center text-block"
    }, [_c('span', [_vm._v("No Records Found")])]) : _vm._e()])]
  ], 2)]), _vm._v(" "), _c('div', {
    staticClass: "tab-pane",
    attrs: {
      "role": "tabpanel",
      "aria-labelledby": "paramTab3PANE",
      "id": "paramTab3PANE"
    }
  }, [_c('p'), _vm._v(" "), _c('h4', {
    staticClass: "timeline-header",
    staticStyle: {
      "text-decoration": "underline",
      "color": "#0073b7"
    }
  }, [_vm._v(" Selected Event Data Params:")]), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
    staticClass: "col-lg-6"
  }, [
    [_c('div', {
      staticClass: "table-responsive",
      staticStyle: {
        "border": "1px solid lightgray"
      },
      style: ({
        height: 350 + 'px'
      }),
      attrs: {
        "id": "selectEVENTparamsTablePane"
      }
    }, [_c('table', {
      staticClass: "table table-bordered table-responsive-stack",
      attrs: {
        "id": "selectEVENTparamsTBl"
      }
    }, [_vm._m(5), _vm._v(" "), (_vm.saveeventselectedParamsList.length != 0) ? _c('tbody', _vm._l((_vm.saveeventselectedParamsList), function(items, iindex) {
      return _c('tr', {
        key: iindex
      }, [_c('td', [_vm._v(_vm._s(iindex + 1))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(items.obis))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(items.def))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(items.assign))])])
    }), 0) : _vm._e()]), _vm._v(" "), (_vm.saveeventselectedParamsList.length == 0) ? _c('div', {
      staticClass: "text-center text-block"
    }, [_c('span', [_vm._v("No Records Found")])]) : _vm._e()])]
  ], 2)]), _vm._v(" "), _c('div', {
    staticClass: "tab-pane",
    attrs: {
      "role": "tabpanel",
      "aria-labelledby": "paramTab4PANE",
      "id": "paramTab4PANE"
    }
  }, [_c('p'), _vm._v(" "), _c('h4', {
    staticClass: "timeline-header",
    staticStyle: {
      "text-decoration": "underline",
      "color": "#0073b7"
    }
  }, [_vm._v(" Selected Midnight Params:")]), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
    staticClass: "col-lg-6"
  }, [
    [_c('div', {
      staticClass: "table-responsive",
      staticStyle: {
        "border": "1px solid lightgray"
      },
      style: ({
        height: 350 + 'px'
      }),
      attrs: {
        "id": "selectMNparamsTablePane"
      }
    }, [_c('table', {
      staticClass: "table table-bordered table-responsive-stack",
      attrs: {
        "id": "selectMNparamsTBl"
      }
    }, [_vm._m(6), _vm._v(" "), (_vm.savemidnightselectedParamsList.length != 0) ? _c('tbody', _vm._l((_vm.savemidnightselectedParamsList), function(items, iindex) {
      return _c('tr', {
        key: iindex
      }, [_c('td', [_vm._v(_vm._s(iindex + 1))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(items.obis))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(items.def))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(items.assign))])])
    }), 0) : _vm._e()]), _vm._v(" "), (_vm.savemidnightselectedParamsList.length == 0) ? _c('div', {
      staticClass: "text-center text-block"
    }, [_c('span', [_vm._v("No Records Found")])]) : _vm._e()])]
  ], 2)]), _vm._v(" "), _c('div', {
    staticClass: "tab-pane",
    attrs: {
      "role": "tabpanel",
      "aria-labelledby": "paramTab5PANE",
      "id": "paramTab5PANE"
    }
  }, [_c('p'), _vm._v(" "), _c('h4', {
    staticClass: "timeline-header",
    staticStyle: {
      "text-decoration": "underline",
      "color": "#0073b7"
    }
  }, [_vm._v(" Selected Billing Params:")]), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
    staticClass: "col-lg-6"
  }, [
    [_c('div', {
      staticClass: "table-responsive",
      staticStyle: {
        "border": "1px solid lightgray"
      },
      style: ({
        height: 350 + 'px'
      }),
      attrs: {
        "id": "selectBILLparamsTablePane"
      }
    }, [_c('table', {
      staticClass: "table table-bordered table-responsive-stack",
      attrs: {
        "id": "selectBILLparamsTBl"
      }
    }, [_vm._m(7), _vm._v(" "), (_vm.savebillingselectedParamsList.length != 0) ? _c('tbody', _vm._l((_vm.savebillingselectedParamsList), function(items, iindex) {
      return _c('tr', {
        key: iindex
      }, [_c('td', [_vm._v(_vm._s(iindex + 1))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(items.obis))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(items.def))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(items.assign))])])
    }), 0) : _vm._e()]), _vm._v(" "), (_vm.savebillingselectedParamsList.length == 0) ? _c('div', {
      staticClass: "text-center text-block"
    }, [_c('span', [_vm._v("No Records Found")])]) : _vm._e()])]
  ], 2)])])])])])])]), _vm._v(" "), _c('li', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (_vm.saveMeterCONFIGpageJSON.DATA.DLMSCfg.MeterType == 'Ethernet'),
      expression: "saveMeterCONFIGpageJSON.DATA.DLMSCfg.MeterType == 'Ethernet'"
    }]
  }, [_c('i', {
    staticClass: "fa fa-sliders bg-yellow"
  }), _vm._v(" "), _c('div', {
    staticClass: "timeline-item"
  }, [_c('span', {
    staticClass: "time"
  }, [_vm._v(" ")]), _vm._v(" "), _c('h3', {
    staticClass: "timeline-header"
  }, [_vm._v("Configuration")]), _vm._v(" "), _c('div', {
    staticClass: "timeline-body"
  }, [_c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-12"
  }, [_vm._m(8), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Enable Instantaneous : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveETHNETInstantaneousTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Enable Load Survey : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveETHNETLoadServeTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Enable Event Data : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveETHNETeventDataTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Enable Midnight : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveETHNETmidnightTXT))])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Enable Midnight : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveETHNETbillingtTXT))])]), _vm._v(" "), _c('p')])]), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-12"
  }, [
    [_c('div', {
      staticClass: "table-responsive",
      staticStyle: {
        "border": "1px solid lightgray"
      },
      attrs: {
        "id": "saveMeterconfigethnetTablePane"
      }
    }, [_c('table', {
      staticClass: "table table-bordered table-responsive-stack",
      attrs: {
        "id": "saveMeterconfigethnetTableID"
      }
    }, [_vm._m(9), _vm._v(" "), (_vm.saveMeterCONFIGpageJSON.DATA.DLMSEthMetCfg.NumMeters != '0') ? _c('tbody', _vm._l((_vm.saveMeterCONFIGpageJSON.DATA.DLMSEthMetCfg.EthMeters), function(inputItems, index) {
      return _c('tr', {
        key: index
      }, [_c('td', [_vm._v(_vm._s(index + 1))]), _vm._v(" "), _c('td', {
        staticClass: "center-block text-center"
      }, [_vm._v(_vm._s(inputItems.Enable == "1" ? "Enable" : "Disable"))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(inputItems.Ip))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(inputItems.Port))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(inputItems.Pwd))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(inputItems.Loc))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(inputItems.TO))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(inputItems.RetCnt))])])
    }), 0) : _vm._e()]), _vm._v(" "), (_vm.saveMeterCONFIGpageJSON.DATA.DLMSEthMetCfg.NumMeters == '0') ? _c('div', {
      staticClass: "text-center text-block"
    }, [_c('span', [_vm._v("No Records Found")])]) : _vm._e()])]
  ], 2)])])])]), _vm._v(" "), _c('li', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (_vm.saveMeterCONFIGpageJSON.DATA.DLMSCfg.MeterType == 'Serial' && _vm.saveMeterCONFIGpageJSON.DATA.DLMSCfg.FaultTolSupp == 'No'),
      expression: "saveMeterCONFIGpageJSON.DATA.DLMSCfg.MeterType == 'Serial' && saveMeterCONFIGpageJSON.DATA.DLMSCfg.FaultTolSupp == 'No'"
    }]
  }, [_c('i', {
    staticClass: "fa fa-sliders bg-yellow"
  }), _vm._v(" "), _c('div', {
    staticClass: "timeline-item"
  }, [_c('h3', {
    staticClass: "timeline-header"
  }, [_vm._v("Meter Configuration")]), _vm._v(" "), _c('div', {
    staticClass: "timeline-body"
  }, [_c('div', {
    staticClass: "row"
  }, [_vm._m(10), _vm._v(" "), _c('div', {
    staticClass: "col-lg-12"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Instantaneous : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveSERIALInstantaneousTXT))]), _vm._v("            \n             \n                       "), _c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Load Survey : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveSERIALLoadServeTXT))]), _vm._v("            \n              \n                       "), _c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Event Data : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveSERIALEventDataTXT))]), _vm._v("            \n         \n                       "), _c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Midnight : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveSERIALMidnightTXT))]), _vm._v("    "), _c('i', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (_vm.saveSERIALMidnightTXT == 'No' ? false : true),
      expression: "saveSERIALMidnightTXT == 'No' ? false : true"
    }],
    staticClass: "fa fa-clock-o",
    attrs: {
      "aria-hidden": "true"
    }
  }), _vm._v("    \n                        "), _c('span', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (_vm.saveSERIALMidnightTXT == 'No' ? false : true),
      expression: "saveSERIALMidnightTXT == 'No' ? false : true"
    }],
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Midnight Poll Period : ")]), _vm._v(" "), _c('span', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (_vm.saveSERIALMidnightTXT == 'No' ? false : true),
      expression: "saveSERIALMidnightTXT == 'No' ? false : true"
    }],
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveSERIALMidnightPeriodTXT))]), _vm._v("        \n           \n                       "), _c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Billing : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveSERIALBillingTXT))]), _vm._v("     "), _c('i', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (_vm.saveSERIALBillingTXT == 'No' ? false : true),
      expression: "saveSERIALBillingTXT == 'No' ? false : true"
    }],
    staticClass: "fa fa-clock-o",
    attrs: {
      "aria-hidden": "true"
    }
  }), _vm._v(" "), _c('span', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (_vm.saveSERIALBillingTXT == 'No' ? false : true),
      expression: "saveSERIALBillingTXT == 'No' ? false : true"
    }],
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Billing Poll Period : ")]), _vm._v(" "), _c('span', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (_vm.saveSERIALBillingTXT == 'No' ? false : true),
      expression: "saveSERIALBillingTXT == 'No' ? false : true"
    }],
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveSERIALBillingPeriodTXT))]), _vm._v("        \n            \n                                      "), _c('p')])]), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-12"
  }, [_c('div', {
    staticClass: "tab",
    attrs: {
      "role": "tabpanel"
    }
  }, [_c('ul', {
    staticClass: "nav nav-tabs",
    attrs: {
      "role": "tablist"
    }
  }, _vm._l((parseInt(_vm.saveDeviceCONFIGpageJSON.DATA.SerPortCfg.NumSerPorts)), function(index) {
    return _c('li', {
      key: index,
      class: [index == 1 ? 'active' : ''],
      attrs: {
        "role": "presentation",
        "id": 'portTab1' + index
      }
    }, [_c('a', {
      staticStyle: {
        "text-transform": "uppercase"
      },
      attrs: {
        "id": 'portTabbutton' + index,
        "href": '#portTabPANE' + index,
        "aria-controls": "home",
        "role": "tab",
        "data-toggle": "tab"
      }
    }, [_c('i', {
      staticClass: "fa fa-sliders iconbg",
      attrs: {
        "aria-hidden": "true"
      }
    }), _vm._v("   Port " + _vm._s(index) + "\n                        ")])])
  }), 0)]), _vm._v(" "), _c('div', {
    staticClass: "tab-content"
  }, _vm._l((parseInt(_vm.saveDeviceCONFIGpageJSON.DATA.SerPortCfg.NumSerPorts)), function(indexx) {
    return _c('div', {
      key: indexx,
      staticClass: "tab-pane",
      class: [indexx == 1 ? 'active' : ''],
      attrs: {
        "role": "tabpanel",
        "aria-labelledby": 'portTabPANE' + indexx,
        "id": 'portTabPANE' + indexx
      }
    }, [_c('p'), _vm._v(" "), _c('h4', {
      staticClass: "timeline-header",
      staticStyle: {
        "text-decoration": "underline",
        "color": "#0073b7"
      }
    }, [_vm._v(" Port " + _vm._s(indexx) + " Configuration:")]), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', [_c('p'), _vm._v(" "), _c('div', {
      staticClass: "row"
    }, [_c('div', {
      staticClass: "col-md-12"
    }, [_vm._m(11, true), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
      staticClass: "row"
    }, [_c('div', {
      staticClass: "col-lg-12"
    }, [_c('span', {
      staticClass: "inputTEXTLBLcss"
    }, [_vm._v("Communication Mode : ")]), _vm._v(" "), _c('span', {
      staticClass: "inputANSWERLBLcss",
      attrs: {
        "id": 'saveSERIALCommModetTXT' + indexx
      }
    }), _vm._v("            \n                   \n                       \n                   \n                       "), _c('span', {
      staticClass: "inputTEXTLBLcss"
    }, [_vm._v("Baud Rate : ")]), _vm._v(" "), _c('span', {
      staticClass: "inputANSWERLBLcss",
      attrs: {
        "id": 'saveSERIALbaudrateTXT' + indexx
      }
    }), _vm._v("            \n                    \n                       "), _c('span', {
      staticClass: "inputTEXTLBLcss"
    }, [_vm._v("Stop Bits : ")]), _vm._v(" "), _c('span', {
      staticClass: "inputANSWERLBLcss",
      attrs: {
        "id": 'saveSERIALstopbitsTXT' + indexx
      }
    }), _vm._v("            \n                    \n                       "), _c('span', {
      staticClass: "inputTEXTLBLcss"
    }, [_vm._v("Parity : ")]), _vm._v(" "), _c('span', {
      staticClass: "inputANSWERLBLcss",
      attrs: {
        "id": 'saveSERIALparityTXT' + indexx
      }
    }), _vm._v("            \n                    \n                       "), _c('span', {
      staticClass: "inputTEXTLBLcss"
    }, [_vm._v("Data : ")]), _vm._v(" "), _c('span', {
      staticClass: "inputANSWERLBLcss",
      attrs: {
        "id": 'saveSERIALdataTXT' + indexx
      }
    }), _vm._v("            \n\n                       "), _c('span', {
      directives: [{
        name: "show",
        rawName: "v-show",
        value: (false),
        expression: "false"
      }],
      staticClass: "inputTEXTLBLcss"
    }, [_vm._v("Hand-Shake : ")]), _vm._v(" "), _c('span', {
      directives: [{
        name: "show",
        rawName: "v-show",
        value: (false),
        expression: "false"
      }],
      staticClass: "inputANSWERLBLcss",
      attrs: {
        "id": 'saveSERIALhandshakeTXT' + indexx
      }
    }), _vm._v("            \n                    ")])]), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
      staticClass: "row"
    }, [_c('div', {
      staticClass: "col-lg-12"
    }, [
      [_c('div', {
        staticClass: "table-responsive",
        staticStyle: {
          "border": "1px solid lightgray"
        },
        attrs: {
          "id": 'meterconfigTablePane' + indexx
        }
      }, [_c('table', {
        staticClass: "table table-bordered table-responsive-stack",
        attrs: {
          "id": 'meterconfigTableID' + indexx
        }
      }, [_vm._m(12, true), _vm._v(" "), (_vm.saveMeterCONFIGpageJSON.DATA['DLMSP' + (indexx - 1) + 'MetCfg'].Meters.length != 0) ? _c('tbody', _vm._l((_vm.saveMeterCONFIGpageJSON.DATA['DLMSP' + (indexx - 1) + 'MetCfg'].Meters), function(dlmsetersItems, dlmsBlockindex) {
        return _c('tr', {
          key: dlmsBlockindex
        }, [_c('td', [_vm._v(_vm._s(dlmsBlockindex + 1))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(dlmsetersItems.Enable == '1' ? "Enable" : "Disable"))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(dlmsetersItems.Addr))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(dlmsetersItems.AddrSz))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(dlmsetersItems.Pwd))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(dlmsetersItems.Loc))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(dlmsetersItems.TO))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(dlmsetersItems.RetCnt))])])
      }), 0) : _vm._e()]), _vm._v(" "), (_vm.saveMeterCONFIGpageJSON.DATA['DLMSP' + (indexx - 1) + 'MetCfg'].Meters.length == 0) ? _c('div', {
        staticClass: "text-center text-block"
      }, [_c('span', [_vm._v("No Records Found")])]) : _vm._e()])]
    ], 2)])])])])])
  }), 0)])])])])]), _vm._v(" "), _c('li', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (_vm.saveMeterCONFIGpageJSON.DATA.DLMSCfg.MeterType == 'Serial' && _vm.saveMeterCONFIGpageJSON.DATA.DLMSCfg.FaultTolSupp == 'Yes'),
      expression: "saveMeterCONFIGpageJSON.DATA.DLMSCfg.MeterType == 'Serial' && saveMeterCONFIGpageJSON.DATA.DLMSCfg.FaultTolSupp == 'Yes'"
    }]
  }, [_c('i', {
    staticClass: "fa fa-sliders bg-yellow"
  }), _vm._v(" "), _c('div', {
    staticClass: "timeline-item"
  }, [_c('div', {
    staticClass: "timeline-body"
  }, [_c('div', {
    staticClass: "row"
  }, [_vm._m(13), _vm._v(" "), _c('div', {
    staticClass: "col-lg-12"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Instantaneous : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveFAULTInstantaneousTXT))]), _vm._v("            \n                       "), _c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Load Survey : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveFAULTLoadServeTXT))]), _vm._v("            \n                       "), _c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Event Data : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveFAULTEventDataTXT))]), _vm._v("            \n                       "), _c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Midnight : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveFAULTMidnightTXT))]), _vm._v("    "), _c('i', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (_vm.saveFAULTMidnightTXT == 'No' ? false : true),
      expression: "saveFAULTMidnightTXT == 'No' ? false : true"
    }],
    staticClass: "fa fa-clock-o",
    attrs: {
      "aria-hidden": "true"
    }
  }), _vm._v(" "), _c('span', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (_vm.saveFAULTMidnightTXT == 'No' ? false : true),
      expression: "saveFAULTMidnightTXT == 'No' ? false : true"
    }],
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Midnight Poll Period : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveFAULTMidnightPeriodTXT))]), _vm._v("            \n                       "), _c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v(" Billing : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveFAULTBillingTXT))]), _vm._v("    "), _c('i', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (_vm.saveFAULTBillingTXT == 'No' ? false : true),
      expression: "saveFAULTBillingTXT == 'No' ? false : true"
    }],
    staticClass: "fa fa-clock-o",
    attrs: {
      "aria-hidden": "true"
    }
  }), _vm._v(" "), _c('span', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (_vm.saveFAULTBillingTXT == 'No' ? false : true),
      expression: "saveFAULTBillingTXT == 'No' ? false : true"
    }],
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Billing Poll Period : ")]), _vm._v(" "), _c('span', {
    staticClass: "inputANSWERLBLcss"
  }, [_vm._v(" " + _vm._s(_vm.saveFAULTBillingPeriodTXT))]), _vm._v("            \n                 "), _c('p')])]), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-12"
  }, [_c('div', {
    staticClass: "tab",
    attrs: {
      "role": "tabpanel"
    }
  }, [_c('ul', {
    staticClass: "nav nav-tabs",
    attrs: {
      "role": "tablist"
    }
  }, _vm._l((parseInt(_vm.saveDeviceCONFIGpageJSON.DATA.SerPortCfg.NumSerPorts)), function(index) {
    return _c('li', {
      key: index,
      class: [index == 1 ? 'active' : ''],
      attrs: {
        "role": "presentation",
        "id": 'portTab1' + index
      }
    }, [_c('a', {
      staticStyle: {
        "text-transform": "uppercase"
      },
      attrs: {
        "id": 'portTabbutton' + index,
        "href": '#portfaultTabPANE' + index,
        "aria-controls": "home",
        "role": "tab",
        "data-toggle": "tab"
      }
    }, [_c('i', {
      staticClass: "fa fa-sliders iconbg",
      attrs: {
        "aria-hidden": "true"
      }
    }), _vm._v("   Ring " + _vm._s(index) + "\n                        ")])])
  }), 0)]), _vm._v(" "), _c('div', {
    staticClass: "tab-content"
  }, _vm._l((parseInt(_vm.saveDeviceCONFIGpageJSON.DATA.SerPortCfg.NumSerPorts)), function(indexx) {
    return _c('div', {
      key: indexx,
      staticClass: "tab-pane",
      class: [indexx == 1 ? 'active' : ''],
      attrs: {
        "role": "tabpanel",
        "aria-labelledby": 'portfaultTabPANE' + indexx,
        "id": 'portfaultTabPANE' + indexx
      }
    }, [_c('p'), _vm._v(" "), _c('h4', {
      staticClass: "timeline-header",
      staticStyle: {
        "text-decoration": "underline",
        "color": "#0073b7"
      }
    }, [_vm._v(" Ring " + _vm._s(indexx) + " Configuration:")]), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', [_c('p'), _vm._v(" "), _c('div', {
      staticClass: "row"
    }, [_c('div', {
      staticClass: "col-md-12"
    }, [_vm._m(14, true), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
      staticClass: "row"
    }, [_c('div', {
      staticClass: "col-lg-12"
    }, [_c('span', {
      staticClass: "inputTEXTLBLcss"
    }, [_vm._v("Communication Mode : ")]), _vm._v(" "), _c('span', {
      staticClass: "inputANSWERLBLcss",
      attrs: {
        "id": 'saveFAULTCommModetTXT' + indexx
      }
    }), _vm._v("            \n                       \n                       "), _c('span', {
      staticClass: "inputTEXTLBLcss"
    }, [_vm._v("Baud Rate : ")]), _vm._v(" "), _c('span', {
      staticClass: "inputANSWERLBLcss",
      attrs: {
        "id": 'saveFAULTbaudrateTXT' + indexx
      }
    }), _vm._v("            \n                       "), _c('span', {
      staticClass: "inputTEXTLBLcss"
    }, [_vm._v("Stop Bits : ")]), _vm._v(" "), _c('span', {
      staticClass: "inputANSWERLBLcss",
      attrs: {
        "id": 'saveFAULTstopbitsTXT' + indexx
      }
    }), _vm._v("            \n                       "), _c('span', {
      staticClass: "inputTEXTLBLcss"
    }, [_vm._v("Parity : ")]), _vm._v(" "), _c('span', {
      staticClass: "inputANSWERLBLcss",
      attrs: {
        "id": 'saveFAULTparityTXT' + indexx
      }
    }), _vm._v("            \n                       "), _c('span', {
      staticClass: "inputTEXTLBLcss"
    }, [_vm._v("Data : ")]), _vm._v(" "), _c('span', {
      staticClass: "inputANSWERLBLcss",
      attrs: {
        "id": 'saveFAULTdataTXT' + indexx
      }
    }), _vm._v("            \n                       "), _c('span', {
      directives: [{
        name: "show",
        rawName: "v-show",
        value: (false),
        expression: "false"
      }],
      staticClass: "inputTEXTLBLcss"
    }, [_vm._v("Hand-Shake : ")]), _vm._v(" "), _c('span', {
      directives: [{
        name: "show",
        rawName: "v-show",
        value: (false),
        expression: "false"
      }],
      staticClass: "inputANSWERLBLcss",
      attrs: {
        "id": 'saveFAULThandshakeTXT' + indexx
      }
    }), _vm._v("            \n                    ")])]), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
      staticClass: "row"
    }, [_c('div', {
      staticClass: "col-lg-12"
    }, [
      [_c('div', {
        staticClass: "table-responsive",
        staticStyle: {
          "border": "1px solid lightgray"
        },
        attrs: {
          "id": 'meterFAULTconfigTablePane' + indexx
        }
      }, [_c('table', {
        staticClass: "table table-bordered table-responsive-stack",
        attrs: {
          "id": 'meterFAULTconfigTableID' + indexx
        }
      }, [_vm._m(15, true), _vm._v(" "), (_vm.saveMeterCONFIGpageJSON.DATA['DLMSP' + (indexx - 1) + 'MetCfg'].Meters.length != 0) ? _c('tbody', _vm._l((_vm.saveMeterCONFIGpageJSON.DATA['DLMSP' + (indexx - 1) + 'MetCfg'].Meters), function(dlmsetersItems, dlmsBlockindex) {
        return _c('tr', {
          key: dlmsBlockindex
        }, [_c('td', [_vm._v(_vm._s(dlmsBlockindex + 1))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(dlmsetersItems.Enable == '1' ? "Enable" : "Disable"))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(dlmsetersItems.Addr))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(dlmsetersItems.AddrSz))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(dlmsetersItems.Pwd))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(dlmsetersItems.Loc))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(dlmsetersItems.TO))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(dlmsetersItems.RetCnt))])])
      }), 0) : _vm._e()]), _vm._v(" "), (_vm.saveMeterCONFIGpageJSON.DATA['DLMSP' + (indexx - 1) + 'MetCfg'].Meters.length == 0) ? _c('div', {
        staticClass: "text-center text-block"
      }, [_c('span', [_vm._v("No Records Found")])]) : _vm._e()])]
    ], 2)])])])])])
  }), 0)])])])])]), _vm._v(" "), _c('li', [_c('i', {
    staticClass: "fa fa-floppy-o bg-yellow"
  }), _vm._v(" "), _c('div', {
    staticClass: "timeline-item"
  }, [_c('h3', {
    staticClass: "timeline-header"
  }), _vm._v(" "), _c('div', {
    staticClass: "timeline-body"
  }, [_c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-12 text-center"
  }, [_c('a', {
    staticClass: "btn btn-success btn-lg",
    on: {
      "click": _vm.saveDCUfuntion
    }
  }, [_c('i', {
    staticClass: "fa fa-floppy-o "
  }), _vm._v(" Save & Apply")])])])])])])])])])], 1)
},staticRenderFns: [function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('h5', [_c('b', [_vm._v("Ethernet -1 Configuration")])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('h5', [_c('b', [_vm._v("Ethernet -2 Configuration")])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('div', {
    staticClass: "tab",
    attrs: {
      "role": "tabpanel"
    }
  }, [_c('ul', {
    staticClass: "nav nav-tabs",
    attrs: {
      "role": "tablist"
    }
  }, [_c('li', {
    staticClass: "active",
    attrs: {
      "role": "presentation",
      "id": "paramTab1"
    }
  }, [_c('a', {
    staticStyle: {
      "text-transform": "uppercase"
    },
    attrs: {
      "id": "paramTab1button",
      "href": "#paramTab1PANE",
      "aria-controls": "home",
      "role": "tab",
      "data-toggle": "tab"
    }
  }, [_c('i', {
    staticClass: "fa fa-th-large iconbg",
    attrs: {
      "aria-hidden": "true"
    }
  }), _vm._v("   Instantaneous\n                        ")])]), _vm._v(" "), _c('li', {
    attrs: {
      "role": "presentation",
      "id": "paramTab2"
    }
  }, [_c('a', {
    staticStyle: {
      "text-transform": "uppercase"
    },
    attrs: {
      "id": "paramTab2button",
      "href": "#paramTab2PANE",
      "aria-controls": "home",
      "role": "tab",
      "data-toggle": "tab"
    }
  }, [_c('i', {
    staticClass: "fa fa-th-large iconbg",
    attrs: {
      "aria-hidden": "true"
    }
  }), _vm._v("   Load Survey\n                        ")])]), _vm._v(" "), _c('li', {
    attrs: {
      "role": "presentation",
      "id": "paramTab3"
    }
  }, [_c('a', {
    staticStyle: {
      "text-transform": "uppercase"
    },
    attrs: {
      "id": "paramTab3button",
      "href": "#paramTab3PANE",
      "aria-controls": "home",
      "role": "tab",
      "data-toggle": "tab"
    }
  }, [_c('i', {
    staticClass: "fa fa-th-large iconbg",
    attrs: {
      "aria-hidden": "true"
    }
  }), _vm._v("   Event Data\n                        ")])]), _vm._v(" "), _c('li', {
    attrs: {
      "role": "presentation",
      "id": "paramTab4"
    }
  }, [_c('a', {
    staticStyle: {
      "text-transform": "uppercase"
    },
    attrs: {
      "id": "paramTab4button",
      "href": "#paramTab4PANE",
      "aria-controls": "home",
      "role": "tab",
      "data-toggle": "tab"
    }
  }, [_c('i', {
    staticClass: "fa fa-th-large iconbg",
    attrs: {
      "aria-hidden": "true"
    }
  }), _vm._v("   Midnight\n                        ")])]), _vm._v(" "), _c('li', {
    attrs: {
      "role": "presentation",
      "id": "paramTab5"
    }
  }, [_c('a', {
    staticStyle: {
      "text-transform": "uppercase"
    },
    attrs: {
      "id": "paramTab5button",
      "href": "#paramTab5PANE",
      "aria-controls": "home",
      "role": "tab",
      "data-toggle": "tab"
    }
  }, [_c('i', {
    staticClass: "fa fa-th-large iconbg",
    attrs: {
      "aria-hidden": "true"
    }
  }), _vm._v("   Billing\n                        ")])])])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('thead', {
    staticStyle: {
      "position": "sticky",
      "top": "-1px",
      "z-index": "1"
    }
  }, [_c('tr', [_c('th', [_vm._v("S.No")]), _vm._v(" "), _c('th', [_vm._v("OBIS Code")]), _vm._v(" "), _c('th', [_vm._v("Default Name")]), _vm._v(" "), _c('th', [_vm._v("User Assign Name")])])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('thead', {
    staticStyle: {
      "position": "sticky",
      "top": "-1px",
      "z-index": "1"
    }
  }, [_c('tr', [_c('th', [_vm._v("S.No")]), _vm._v(" "), _c('th', [_vm._v("OBIS Code")]), _vm._v(" "), _c('th', [_vm._v("Default Name")]), _vm._v(" "), _c('th', [_vm._v("User Assign Name")])])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('thead', {
    staticStyle: {
      "position": "sticky",
      "top": "-1px",
      "z-index": "1"
    }
  }, [_c('tr', [_c('th', [_vm._v("S.No")]), _vm._v(" "), _c('th', [_vm._v("OBIS Code")]), _vm._v(" "), _c('th', [_vm._v("Default Name")]), _vm._v(" "), _c('th', [_vm._v("User Assign Name")])])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('thead', {
    staticStyle: {
      "position": "sticky",
      "top": "-1px",
      "z-index": "1"
    }
  }, [_c('tr', [_c('th', [_vm._v("S.No")]), _vm._v(" "), _c('th', [_vm._v("OBIS Code")]), _vm._v(" "), _c('th', [_vm._v("Default Name")]), _vm._v(" "), _c('th', [_vm._v("User Assign Name")])])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('thead', {
    staticStyle: {
      "position": "sticky",
      "top": "-1px",
      "z-index": "1"
    }
  }, [_c('tr', [_c('th', [_vm._v("S.No")]), _vm._v(" "), _c('th', [_vm._v("OBIS Code")]), _vm._v(" "), _c('th', [_vm._v("Default Name")]), _vm._v(" "), _c('th', [_vm._v("User Assign Name")])])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('h4', [_c('p', [_vm._v("Data Poll Configuration")])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('thead', {
    staticStyle: {
      "position": "sticky",
      "top": "-1px",
      "z-index": "1"
    }
  }, [_c('tr', [_c('th', [_vm._v("S.No")]), _vm._v(" "), _c('th', {
    staticStyle: {
      "width": "150px"
    }
  }, [_vm._v("Enable")]), _vm._v(" "), _c('th', [_vm._v("Meter IP")]), _vm._v(" "), _c('th', [_vm._v("Port")]), _vm._v(" "), _c('th', [_vm._v("Password")]), _vm._v(" "), _c('th', [_vm._v("Location")]), _vm._v(" "), _c('th', [_vm._v("Timeout (in Sec)")]), _vm._v(" "), _c('th', [_vm._v("Ret Count")])])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('div', {
    staticClass: "col-lg-12"
  }, [_c('h5', [_c('b', [_vm._v("Data Poll Configuration")])]), _vm._v(" "), _c('p')])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('h5', [_c('b', [_vm._v("Serial Configuration")])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('thead', {
    staticStyle: {
      "position": "sticky",
      "top": "-1px",
      "z-index": "1"
    }
  }, [_c('tr', [_c('th', [_vm._v("S.No")]), _vm._v(" "), _c('th', {
    staticStyle: {
      "width": "150px"
    }
  }, [_vm._v("Enable")]), _vm._v(" "), _c('th', [_vm._v("Meter IP Address")]), _vm._v(" "), _c('th', [_vm._v("Address Size")]), _vm._v(" "), _c('th', [_vm._v("Password")]), _vm._v(" "), _c('th', [_vm._v("Meter Location")]), _vm._v(" "), _c('th', [_vm._v("Timeout (in Sec)")]), _vm._v(" "), _c('th', [_vm._v("Ret Count")])])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('div', {
    staticClass: "col-lg-12"
  }, [_c('h5', [_c('b', [_vm._v("Data Poll Configuration")])]), _vm._v(" "), _c('p')])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('h5', [_c('b', [_vm._v("Serial Configuration")])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('thead', {
    staticStyle: {
      "position": "sticky",
      "top": "-1px",
      "z-index": "1"
    }
  }, [_c('tr', [_c('th', [_vm._v("S.No")]), _vm._v(" "), _c('th', {
    staticStyle: {
      "width": "150px"
    }
  }, [_vm._v("Enable")]), _vm._v(" "), _c('th', [_vm._v("Meter IP Address")]), _vm._v(" "), _c('th', [_vm._v("Address Size")]), _vm._v(" "), _c('th', [_vm._v("Password")]), _vm._v(" "), _c('th', [_vm._v("Meter Location")]), _vm._v(" "), _c('th', [_vm._v("Timeout (in Sec)")]), _vm._v(" "), _c('th', [_vm._v("Ret Count")])])])
}]}

/***/ }),
/* 122 */
/***/ (function(module, exports) {

module.exports={render:function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('section', {
    staticClass: "content",
    attrs: {
      "id": "uploadFirmwarepane"
    }
  }, [_c('vue-element-loading', {
    attrs: {
      "active": _vm.isLoading,
      "spinner": "spinner",
      "color": "#000",
      "is-full-screen": true
    }
  }), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-12"
  }, [_c('ul', {
    staticClass: "timeline"
  }, [_vm._m(0), _vm._v(" "), _c('li', [_c('i', {
    staticClass: "fa fa-upload bg-blue"
  }), _vm._v(" "), _c('div', {
    staticClass: "timeline-item"
  }, [_c('span', {
    staticClass: "time"
  }, [_vm._v(" ")]), _vm._v(" "), _c('h3', {
    staticClass: "timeline-header"
  }, [_vm._v("Update Configuration")]), _vm._v(" "), _c('div', {
    staticClass: "timeline-body"
  }, [_c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-12"
  }, [_c('input', {
    ref: "file1",
    attrs: {
      "type": "file",
      "id": "file1"
    },
    on: {
      "change": function($event) {
        return _vm.handleFile1Upload()
      }
    }
  }), _vm._v(" "), _c('p'), _vm._v(" "), _c('button', {
    staticClass: "btn btn-sm btn-default",
    attrs: {
      "id": "upload_BTN",
      "type": "button"
    },
    on: {
      "click": function($event) {
        return _vm.submitFile1()
      }
    }
  }, [_vm._v("\n                         Upload and Apply\n                      ")])])])])])]), _vm._v(" "), _c('li', [_c('i', {
    staticClass: "fa fa-upload bg-red"
  }), _vm._v(" "), _c('div', {
    staticClass: "timeline-item"
  }, [_c('span', {
    staticClass: "time"
  }, [_vm._v(" ")]), _vm._v(" "), _c('h3', {
    staticClass: "timeline-header"
  }, [_vm._v("Update Firmware")]), _vm._v(" "), _c('div', {
    staticClass: "timeline-body"
  }, [_c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-12"
  }, [_c('input', {
    ref: "file2",
    attrs: {
      "type": "file",
      "id": "file2"
    },
    on: {
      "change": function($event) {
        return _vm.handleFile2Upload()
      }
    }
  }), _vm._v(" "), _c('p'), _vm._v(" "), _c('button', {
    staticClass: "btn btn-sm btn-default",
    attrs: {
      "id": "upload_BTN",
      "type": "button"
    },
    on: {
      "click": function($event) {
        return _vm.submitFile2()
      }
    }
  }, [_vm._v("\n                          Upload and Apply\n                    ")])])])])])])])])])], 1)
},staticRenderFns: [function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('li', [_c('i', {
    staticClass: "fa fa-download bg-yellow"
  }), _vm._v(" "), _c('div', {
    staticClass: "timeline-item"
  }, [_c('span', {
    staticClass: "time"
  }, [_vm._v(" ")]), _vm._v(" "), _c('h3', {
    staticClass: "timeline-header"
  }, [_vm._v("Download Configuration")]), _vm._v(" "), _c('div', {
    staticClass: "timeline-body"
  }, [_c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-12"
  }, [_c('button', {
    staticClass: "btn btn-default btn-md",
    attrs: {
      "type": "submit"
    }
  }, [_vm._v("Download")])])])])])])
}]}

/***/ }),
/* 123 */
/***/ (function(module, exports) {

module.exports={render:function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('section', {
    staticClass: "content",
    attrs: {
      "id": "diagnosticPage"
    }
  }, [_c('vue-element-loading', {
    attrs: {
      "active": _vm.isLoading,
      "spinner": "spinner",
      "color": "#000",
      "is-full-screen": true
    }
  }), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-12"
  }, [_c('ul', {
    staticClass: "timeline"
  }, [_c('li', [_c('i', {
    staticClass: "fa fa-search-plus bg-yellow"
  }), _vm._v(" "), _c('div', {
    staticClass: "timeline-item"
  }, [_vm._m(0), _vm._v(" "), _c('h3', {
    staticClass: "timeline-header"
  }, [_vm._v("Diagnostic ")]), _vm._v(" "), _c('div', {
    staticClass: "timeline-body"
  }, [_c('div', {
    staticClass: "row"
  }, [_vm._m(1), _vm._v(" "), _c('div', {
    staticClass: "col-lg-3"
  }, [_c('select', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.diagcategoryTXT),
      expression: "diagcategoryTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "name": "diagcategory",
      "id": "diagcategoryTXT"
    },
    on: {
      "change": function($event) {
        var $$selectedVal = Array.prototype.filter.call($event.target.options, function(o) {
          return o.selected
        }).map(function(o) {
          var val = "_value" in o ? o._value : o.value;
          return val
        });
        _vm.diagcategoryTXT = $event.target.multiple ? $$selectedVal : $$selectedVal[0]
      }
    }
  }, [_c('option', {
    attrs: {
      "value": "Choose Category",
      "selected": "",
      "disabled": ""
    }
  }, [_vm._v("Choose Category")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "ALL DIAG"
    }
  }, [_vm._v("ALL DIAG")])])])]), _vm._v(" "), _c('p'), _vm._v(" "), _vm._m(2), _vm._v(" "), _c('p'), _vm._v(" "), _vm._m(3), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-12"
  }, [
    [_c('div', {
      staticClass: "table-responsive",
      staticStyle: {
        "border": "1px solid lightgray"
      },
      style: ({
        height: _vm.diagnosticTXTareaheight
      }),
      attrs: {
        "id": "diagnosticTXTareaPANE"
      }
    }, [_vm._v("\n\n14-Aug-2020 11:29:28 : Ftp Push option is not enabled so data is not sending to ftp server"), _c('br'), _vm._v("\n14-Aug-2020 11:29:28 : No 104 Master is Up."), _c('br'), _vm._v("\n14-Aug-2020 11:29:28 : Ftp Push option is not enabled so data is not sending to ftp server"), _c('br'), _vm._v("\n14-Aug-2020 11:29:28 : No 104 Master is Up."), _c('br'), _vm._v("\n14-Aug-2020 11:29:28 : Ftp Push option is not enabled so data is not sending to ftp server"), _c('br'), _vm._v("\n14-Aug-2020 11:29:28 : No 104 Master is Up."), _c('br'), _vm._v("\n14-Aug-2020 11:29:28 : Ftp Push option is not enabled so data is not sending to ftp server"), _c('br'), _vm._v("\n14-Aug-2020 11:29:28 : No 104 Master is Up."), _c('br'), _vm._v("\n14-Aug-2020 11:29:28 : Ftp Push option is not enabled so data is not sending to ftp server"), _c('br'), _vm._v("\n14-Aug-2020 11:29:28 : No 104 Master is Up."), _c('br'), _vm._v("\n14-Aug-2020 11:29:28 : Ftp Push option is not enabled so data is not sending to ftp server"), _c('br'), _vm._v("\n14-Aug-2020 11:29:28 : No 104 Master is Up."), _c('br'), _vm._v("\n14-Aug-2020 11:29:28 : Ftp Push option is not enabled so data is not sending to ftp server"), _c('br'), _vm._v("\n14-Aug-2020 11:29:28 : No 104 Master is Up."), _c('br'), _vm._v("\n14-Aug-2020 11:29:28 : Ftp Push option is not enabled so data is not sending to ftp server"), _c('br'), _vm._v("\n14-Aug-2020 11:29:28 : No 104 Master is Up."), _c('br'), _vm._v("\n14-Aug-2020 11:29:28 : Ftp Push option is not enabled so data is not sending to ftp server"), _c('br'), _vm._v("\n14-Aug-2020 11:29:28 : No 104 Master is Up."), _c('br'), _vm._v("\n14-Aug-2020 11:29:28 : Ftp Push option is not enabled so data is not sending to ftp server"), _c('br'), _vm._v("\n14-Aug-2020 11:29:28 : No 104 Master is Up."), _c('br'), _vm._v("\n14-Aug-2020 11:29:28 : Ftp Push option is not enabled so data is not sending to ftp server"), _c('br'), _vm._v("\n14-Aug-2020 11:29:28 : No 104 Master is Up."), _c('br'), _vm._v("\n14-Aug-2020 11:29:28 : Ftp Push option is not enabled so data is not sending to ftp server"), _c('br'), _vm._v("\n14-Aug-2020 11:29:28 : No 104 Master is Up."), _c('br')])]
  ], 2)])])])])])])])], 1)
},staticRenderFns: [function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('span', {
    staticClass: "time",
    staticStyle: {
      "margin-top": "-5px"
    }
  }, [_c('button', {
    staticClass: "btn btn-success btn-sm"
  }, [_vm._v("Enable")]), _vm._v(" \n        "), _c('button', {
    staticClass: "btn btn-default btn-sm"
  }, [_vm._v("Disable")]), _vm._v(" \n        "), _c('button', {
    staticClass: "btn btn-warning btn-sm"
  }, [_vm._v("Clear")]), _vm._v(" \n        "), _c('button', {
    staticClass: "btn btn-warning btn-sm"
  }, [_vm._v("Export")])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Select Diag Category:")])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-2"
  }), _vm._v(" "), _c('div', {
    staticClass: "col-lg-4"
  }, [_c('button', {
    staticClass: "btn btn-sm btn-default",
    attrs: {
      "id": "viewdataApplyBTN",
      "type": "button"
    }
  }, [_vm._v("\n                            Apply\n                      ")])])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-2"
  }, [_c('h5', [_c('b', [_vm._v("Preview :")])])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-4"
  })])
}]}

/***/ }),
/* 124 */
/***/ (function(module, exports) {

module.exports={render:function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('li', {
    staticClass: "dropdown user user-menu"
  }, [_c('a', {
    staticClass: "dropdown-toggle",
    attrs: {
      "href": "javascript:;",
      "data-toggle": "dropdown"
    },
    on: {
      "click": _vm.logoutAction
    }
  }, [_c('img', {
    staticClass: "user-image",
    attrs: {
      "src": "/static/img/images/dculogo2.png"
    }
  }), _vm._v(" "), _c('span', {
    staticClass: "hidden-xs"
  }, [_vm._v("Logout")])]), _vm._v(" "), _c('ul', {
    staticClass: "dropdown-menu"
  }, [_vm._m(0), _vm._v(" "), _c('li', {
    staticClass: "user-footer",
    on: {
      "click": _vm.logoutAction
    }
  }, [_vm._m(1)])])])
},staticRenderFns: [function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('li', {
    staticClass: "user-header",
    staticStyle: {
      "height": "auto",
      "min-height": "85px",
      "padding-bottom": "15px"
    }
  }, [_c('p', [_c('small', [_vm._v("--Admin--")]), _vm._v(" "), _c('small', [_vm._v("DCU")])])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('a', {
    staticClass: "btn btn-default btn-flat btn-block",
    attrs: {
      "href": "javascript:;"
    }
  }, [_c('i', {
    staticClass: "fa fa-sign-out"
  }), _vm._v(" "), _c('span', [_vm._v("Logout")])])
}]}

/***/ }),
/* 125 */
/***/ (function(module, exports) {

module.exports={render:function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('section', {
    staticClass: "content",
    attrs: {
      "id": "generalsettingPagePANE"
    }
  }, [_c('vue-element-loading', {
    attrs: {
      "active": _vm.isLoading,
      "spinner": "spinner",
      "color": "#000",
      "is-full-screen": true
    }
  }), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-12"
  }, [_c('ul', {
    staticClass: "timeline"
  }, [_c('li', [_c('i', {
    staticClass: "fa fa-cog"
  }), _vm._v(" "), _c('div', {
    staticClass: "timeline-item"
  }, [_c('h3', {
    staticClass: "timeline-header"
  }, [_vm._v("General Settings")]), _vm._v(" "), _c('div', {
    staticClass: "timeline-body"
  }, [_c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("DCU ID : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.gendcuserialIDTXT),
      expression: "gendcuserialIDTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "gendcuserialIDTXT",
      "placeholder": "DCU ID",
      "maxlength": "32"
    },
    domProps: {
      "value": (_vm.gendcuserialIDTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "keypress": _vm.isNumber,
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.gendcuserialIDTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("DCU Location : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.gendculocTXT),
      expression: "gendculocTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "gendculocTXT",
      "placeholder": "DCU Location",
      "maxlength": "32"
    },
    domProps: {
      "value": (_vm.gendculocTXT)
    },
    on: {
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.gendculocTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Serial Number : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.gendcuserialNumTXT),
      expression: "gendcuserialNumTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "gendcuserialNumTXT",
      "placeholder": "Serial Number",
      "maxlength": "32",
      "disabled": true
    },
    domProps: {
      "value": (_vm.gendcuserialNumTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.gendcuserialNumTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2",
    staticStyle: {
      "margin-top": "25px",
      "text-align": "center"
    }
  }, [_c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.dbgEnablecheckbox),
      expression: "dbgEnablecheckbox"
    }],
    attrs: {
      "type": "checkbox",
      "id": "dbgEnablecheckbox"
    },
    domProps: {
      "checked": Array.isArray(_vm.dbgEnablecheckbox) ? _vm._i(_vm.dbgEnablecheckbox, null) > -1 : (_vm.dbgEnablecheckbox)
    },
    on: {
      "change": function($event) {
        var $$a = _vm.dbgEnablecheckbox,
          $$el = $event.target,
          $$c = $$el.checked ? (true) : (false);
        if (Array.isArray($$a)) {
          var $$v = null,
            $$i = _vm._i($$a, $$v);
          if ($$el.checked) {
            $$i < 0 && (_vm.dbgEnablecheckbox = $$a.concat([$$v]))
          } else {
            $$i > -1 && (_vm.dbgEnablecheckbox = $$a.slice(0, $$i).concat($$a.slice($$i + 1)))
          }
        } else {
          _vm.dbgEnablecheckbox = $$c
        }
      }
    }
  }), _vm._v(" "), _c('label', {
    staticClass: "inputcheckTEXTLBLcss",
    attrs: {
      "for": "dbgEnablecheckbox"
    }
  }, [_vm._v("Enable Dbg Log ")])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Dbg Log Level : ")]), _vm._v(" "), _c('select', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.dbgloglvlTXT),
      expression: "dbgloglvlTXT"
    }],
    staticClass: "inputTEXTcss",
    staticStyle: {
      "width": "100%",
      "color": "#000"
    },
    attrs: {
      "name": "dbgloglvlTXT",
      "id": "dbgloglvlTXT",
      "disabled": !_vm.dbgEnablecheckbox
    },
    on: {
      "change": function($event) {
        var $$selectedVal = Array.prototype.filter.call($event.target.options, function(o) {
          return o.selected
        }).map(function(o) {
          var val = "_value" in o ? o._value : o.value;
          return val
        });
        _vm.dbgloglvlTXT = $event.target.multiple ? $$selectedVal : $$selectedVal[0]
      }
    }
  }, [_c('option', {
    attrs: {
      "value": "choose Dbg Log Level",
      "selected": ""
    }
  }, [_vm._v("choose Dbg Log Level")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "1"
    }
  }, [_vm._v("All")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "2"
    }
  }, [_vm._v("Critical")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "3"
    }
  }, [_vm._v("Alarms")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "4"
    }
  }, [_vm._v("Warnings")])])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Dbg Log Ip : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.dbglogIPTXT),
      expression: "dbglogIPTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "dbglogIPTXT",
      "placeholder": "Dbg Log Ip",
      "maxlength": "32",
      "disabled": !_vm.dbgEnablecheckbox
    },
    domProps: {
      "value": (_vm.dbglogIPTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.dbglogIPTXT = $event.target.value
      }
    }
  })])]), _vm._v(" "), _c('div', {
    staticStyle: {
      "height": "15px"
    }
  })])])]), _vm._v(" "), _c('li', [_c('i', {
    staticClass: "fa fa-cog"
  }), _vm._v(" "), _c('div', {
    staticClass: "timeline-item"
  }, [_c('h3', {
    staticClass: "timeline-header"
  }, [_vm._v("LAN Settings")]), _vm._v(" "), _c('div', {
    staticClass: "timeline-body"
  }, [_c('div', {
    attrs: {
      "id": "eth1PANE"
    }
  }, [_vm._m(0), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-3"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Current IP Address : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.lancurrIpTXT),
      expression: "lancurrIpTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "lancurrIpTXT",
      "placeholder": "Current IP Address",
      "title": "Range : 1 ~ 254",
      "maxlength": "32",
      "disabled": true
    },
    domProps: {
      "value": (_vm.lancurrIpTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.lancurrIpTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-3"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("New IP Address : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.lannewIpTXT),
      expression: "lannewIpTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "lannewIpTXT",
      "placeholder": "New IP Address",
      "title": "Range : 1 ~ 254",
      "maxlength": "32"
    },
    domProps: {
      "value": (_vm.lannewIpTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.lannewIpTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-3"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Subnet Mask : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.lansubnetmaskIpTXT),
      expression: "lansubnetmaskIpTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "lansubnetmaskIpTXT",
      "placeholder": "Subnet Mask",
      "title": "Range : 1 ~ 254",
      "maxlength": "32"
    },
    domProps: {
      "value": (_vm.lansubnetmaskIpTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.lansubnetmaskIpTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-3"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Gateway : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.langatewayIpTXT),
      expression: "langatewayIpTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "langatewayIpTXT",
      "placeholder": "Gateway",
      "title": "Range : 1 ~ 254",
      "maxlength": "32"
    },
    domProps: {
      "value": (_vm.langatewayIpTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.langatewayIpTXT = $event.target.value
      }
    }
  })])]), _vm._v(" "), _c('div', {
    staticStyle: {
      "height": "15px"
    }
  })]), _vm._v(" "), _c('div', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (_vm.ethnetcount == 2),
      expression: "ethnetcount == 2"
    }],
    attrs: {
      "id": "eth2PANE"
    }
  }, [_vm._m(1), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-3"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Current IP Address : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.lancurrIp2TXT),
      expression: "lancurrIp2TXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "lancurrIp2TXT",
      "placeholder": "Current IP Address",
      "title": "Range : 1 ~ 254",
      "maxlength": "32",
      "disabled": true
    },
    domProps: {
      "value": (_vm.lancurrIp2TXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.lancurrIp2TXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-3"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("New IP Address : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.lannewIp2TXT),
      expression: "lannewIp2TXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "lannewIp2TXT",
      "placeholder": "New IP Address",
      "title": "Range : 1 ~ 254",
      "maxlength": "32"
    },
    domProps: {
      "value": (_vm.lannewIp2TXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.lannewIp2TXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-3"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Subnet Mask : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.lansubnetmaskIp2TXT),
      expression: "lansubnetmaskIp2TXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "lansubnetmaskIp2TXT",
      "placeholder": "Subnet Mask",
      "title": "Range : 1 ~ 254",
      "maxlength": "32"
    },
    domProps: {
      "value": (_vm.lansubnetmaskIp2TXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.lansubnetmaskIp2TXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-3"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Gateway : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.langatewayIp2TXT),
      expression: "langatewayIp2TXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "langatewayIp2TXT",
      "placeholder": "Gateway",
      "title": "Range : 1 ~ 254",
      "maxlength": "32"
    },
    domProps: {
      "value": (_vm.langatewayIp2TXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.langatewayIp2TXT = $event.target.value
      }
    }
  })])]), _vm._v(" "), _c('div', {
    staticStyle: {
      "height": "15px"
    }
  })])])])]), _vm._v(" "), _c('li', [_c('i', {
    staticClass: "fa fa-cog"
  }), _vm._v(" "), _c('div', {
    staticClass: "timeline-item"
  }, [_c('h3', {
    staticClass: "timeline-header"
  }, [_vm._v("Modem Settings            \n                       "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.modemEnablechekbox),
      expression: "modemEnablechekbox"
    }],
    attrs: {
      "type": "checkbox",
      "id": "modemEnablechekbox"
    },
    domProps: {
      "checked": Array.isArray(_vm.modemEnablechekbox) ? _vm._i(_vm.modemEnablechekbox, null) > -1 : (_vm.modemEnablechekbox)
    },
    on: {
      "change": function($event) {
        var $$a = _vm.modemEnablechekbox,
          $$el = $event.target,
          $$c = $$el.checked ? (true) : (false);
        if (Array.isArray($$a)) {
          var $$v = null,
            $$i = _vm._i($$a, $$v);
          if ($$el.checked) {
            $$i < 0 && (_vm.modemEnablechekbox = $$a.concat([$$v]))
          } else {
            $$i > -1 && (_vm.modemEnablechekbox = $$a.slice(0, $$i).concat($$a.slice($$i + 1)))
          }
        } else {
          _vm.modemEnablechekbox = $$c
        }
      }
    }
  }), _vm._v(" "), _c('label', {
    staticClass: "inputcheckTEXTLBLcss",
    attrs: {
      "for": "modemEnablechekbox"
    }
  }, [_vm._v("Enable ")])]), _vm._v(" "), _c('div', {
    staticClass: "timeline-body"
  }, [_c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-3"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("UserName : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.modemUsernameTXT),
      expression: "modemUsernameTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "modemUsernameTXT",
      "placeholder": "UserName",
      "maxlength": "32",
      "disabled": !_vm.modemEnablechekbox
    },
    domProps: {
      "value": (_vm.modemUsernameTXT)
    },
    on: {
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.modemUsernameTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-3"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Password : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.modemPasswordTXT),
      expression: "modemPasswordTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "modemPasswordTXT",
      "placeholder": "Password",
      "maxlength": "32",
      "disabled": !_vm.modemEnablechekbox
    },
    domProps: {
      "value": (_vm.modemPasswordTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.modemPasswordTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-3"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Phone Number : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.modemPhoneTXT),
      expression: "modemPhoneTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "modemPhoneTXT",
      "placeholder": "Phone Number",
      "maxlength": "10",
      "disabled": !_vm.modemEnablechekbox
    },
    domProps: {
      "value": (_vm.modemPhoneTXT)
    },
    on: {
      "keypress": _vm.isNumber,
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.modemPhoneTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-3"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("APN :             ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.modemAPNTXT),
      expression: "modemAPNTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "modemAPNTXT",
      "placeholder": "APN address",
      "maxlength": "32",
      "disabled": !_vm.modemEnablechekbox
    },
    domProps: {
      "value": (_vm.modemAPNTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.modemAPNTXT = $event.target.value
      }
    }
  })])]), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-3",
    staticStyle: {
      "margin-top": "20px",
      "text-align": "center"
    }
  }, [_c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.pingEnablenethealthchekbox),
      expression: "pingEnablenethealthchekbox"
    }],
    attrs: {
      "type": "checkbox",
      "id": "pingEnablenethealthchekbox",
      "disabled": !_vm.modemEnablechekbox
    },
    domProps: {
      "checked": Array.isArray(_vm.pingEnablenethealthchekbox) ? _vm._i(_vm.pingEnablenethealthchekbox, null) > -1 : (_vm.pingEnablenethealthchekbox)
    },
    on: {
      "change": function($event) {
        var $$a = _vm.pingEnablenethealthchekbox,
          $$el = $event.target,
          $$c = $$el.checked ? (true) : (false);
        if (Array.isArray($$a)) {
          var $$v = null,
            $$i = _vm._i($$a, $$v);
          if ($$el.checked) {
            $$i < 0 && (_vm.pingEnablenethealthchekbox = $$a.concat([$$v]))
          } else {
            $$i > -1 && (_vm.pingEnablenethealthchekbox = $$a.slice(0, $$i).concat($$a.slice($$i + 1)))
          }
        } else {
          _vm.pingEnablenethealthchekbox = $$c
        }
      }
    }
  }), _vm._v(" "), _c('label', {
    staticClass: "inputcheckTEXTLBLcss",
    attrs: {
      "for": "pingEnablenethealthchekbox"
    }
  }, [_vm._v("Enable Ping")])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-3"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Ping IP : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.modemPingIPTXT),
      expression: "modemPingIPTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "modemPingIPTXT",
      "placeholder": "Ping IP",
      "maxlength": "32",
      "disabled": !_vm.pingEnablenethealthchekbox || !_vm.modemEnablechekbox
    },
    domProps: {
      "value": (_vm.modemPingIPTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.modemPingIPTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-3"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Ping Interval( in sec) : ")]), _vm._v(" "), _c('select', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.modemPingIntervalTXT),
      expression: "modemPingIntervalTXT"
    }],
    staticClass: "inputTEXTcss",
    staticStyle: {
      "width": "100%",
      "color": "#000"
    },
    attrs: {
      "name": "modemPingIntervalTXT",
      "id": "modemPingIntervalTXT",
      "disabled": !_vm.pingEnablenethealthchekbox || !_vm.modemEnablechekbox
    },
    on: {
      "change": function($event) {
        var $$selectedVal = Array.prototype.filter.call($event.target.options, function(o) {
          return o.selected
        }).map(function(o) {
          var val = "_value" in o ? o._value : o.value;
          return val
        });
        _vm.modemPingIntervalTXT = $event.target.multiple ? $$selectedVal : $$selectedVal[0]
      }
    }
  }, [_c('option', {
    attrs: {
      "value": "choose ping interval",
      "selected": ""
    }
  }, [_vm._v("choose ping interval")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "15"
    }
  }, [_vm._v("15")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "30"
    }
  }, [_vm._v("30")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "45"
    }
  }, [_vm._v("45")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "60"
    }
  }, [_vm._v("60")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "120"
    }
  }, [_vm._v("120")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "240"
    }
  }, [_vm._v("240")])])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-3"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Num of Pings :")]), _vm._v(" "), _c('select', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.modemNumofPingTXT),
      expression: "modemNumofPingTXT"
    }],
    staticClass: "inputTEXTcss",
    staticStyle: {
      "width": "100%",
      "color": "#000"
    },
    attrs: {
      "name": "modemNumofPingTXT",
      "id": "modemNumofPingTXT",
      "disabled": !_vm.pingEnablenethealthchekbox || !_vm.modemEnablechekbox
    },
    on: {
      "change": function($event) {
        var $$selectedVal = Array.prototype.filter.call($event.target.options, function(o) {
          return o.selected
        }).map(function(o) {
          var val = "_value" in o ? o._value : o.value;
          return val
        });
        _vm.modemNumofPingTXT = $event.target.multiple ? $$selectedVal : $$selectedVal[0]
      }
    }
  }, [_c('option', {
    attrs: {
      "value": "choose no of ping",
      "selected": ""
    }
  }, [_vm._v("choose no of ping")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "5"
    }
  }, [_vm._v("5")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "10"
    }
  }, [_vm._v("10")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "15"
    }
  }, [_vm._v("15")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "20"
    }
  }, [_vm._v("20")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "30"
    }
  }, [_vm._v("30")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "50"
    }
  }, [_vm._v("50")])])])]), _vm._v(" "), _c('hr', {
    staticStyle: {
      "margin-top": "15px",
      "margin-bottom": "5px"
    }
  }), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-3"
  }, [_c('label', {
    staticClass: "inputcheckTEXTLBLcss"
  }, [_c('b', [_vm._v("SMS (Reporting & Command)")]), _vm._v("            \n                       "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.smbEnableSMShekbox),
      expression: "smbEnableSMShekbox"
    }],
    attrs: {
      "type": "checkbox",
      "id": "smbEnableSMShekbox"
    },
    domProps: {
      "checked": Array.isArray(_vm.smbEnableSMShekbox) ? _vm._i(_vm.smbEnableSMShekbox, null) > -1 : (_vm.smbEnableSMShekbox)
    },
    on: {
      "click": function($event) {
        return _vm.smsenablefunction()
      },
      "change": function($event) {
        var $$a = _vm.smbEnableSMShekbox,
          $$el = $event.target,
          $$c = $$el.checked ? (true) : (false);
        if (Array.isArray($$a)) {
          var $$v = null,
            $$i = _vm._i($$a, $$v);
          if ($$el.checked) {
            $$i < 0 && (_vm.smbEnableSMShekbox = $$a.concat([$$v]))
          } else {
            $$i > -1 && (_vm.smbEnableSMShekbox = $$a.slice(0, $$i).concat($$a.slice($$i + 1)))
          }
        } else {
          _vm.smbEnableSMShekbox = $$c
        }
      }
    }
  }), _vm._v(" "), _c('label', {
    staticClass: "inputcheckTEXTLBLcss",
    attrs: {
      "for": "smbEnableSMShekbox"
    }
  }, [_vm._v("Enable ")])])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-4"
  }, [_c('img', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (_vm.smbEnableSMShekbox),
      expression: "smbEnableSMShekbox"
    }],
    staticClass: "text-right",
    staticStyle: {
      "cursor": "pointer",
      "margin-left": "-20px",
      "margin-top": "5px",
      "position": "absolute"
    },
    attrs: {
      "id": "smsaddBTN",
      "title": "Add",
      "src": "/static/img/images/add20.png",
      "width": "13"
    },
    on: {
      "click": _vm.addSMScount
    }
  }), _vm._v(" "), _c('img', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (_vm.smbEnableSMShekbox),
      expression: "smbEnableSMShekbox"
    }],
    staticClass: "text-right",
    staticStyle: {
      "cursor": "pointer",
      "position": "absolute",
      "margin-top": "4px"
    },
    attrs: {
      "id": "smsdeleteBTN",
      "title": "Delete",
      "src": "/static/img/images/cancel1.png",
      "width": "15"
    },
    on: {
      "click": _vm.deleteSMScount
    }
  })])]), _vm._v(" "), _vm._l((_vm.smsnumberDetailsArray), function(items, index) {
    return _c('div', {
      key: index,
      staticClass: "row",
      staticStyle: {
        "padding": "5px"
      }
    }, [_c('div', {
      staticClass: "col-lg-3"
    }, [_c('span', {
      staticClass: "inputTEXTLBLcss"
    }, [_vm._v("Name : ")]), _vm._v(" "), _c('input', {
      staticClass: "inputTEXTcss",
      attrs: {
        "id": 'smsNAMETXT' + (index + 1),
        "placeholder": "Name",
        "maxlength": "32",
        "disabled": !_vm.smbEnableSMShekbox
      },
      domProps: {
        "value": items.Name
      },
      on: {
        "change": _vm.saveDeviceConfig
      }
    })]), _vm._v(" "), _c('div', {
      staticClass: "col-lg-3"
    }, [_c('span', {
      staticClass: "inputTEXTLBLcss"
    }, [_vm._v("Phone Number : ")]), _vm._v(" "), _c('input', {
      staticClass: "inputTEXTcss",
      attrs: {
        "id": 'smsphNUMTXT' + (index + 1),
        "placeholder": "Phone Number",
        "maxlength": "10",
        "disabled": !_vm.smbEnableSMShekbox
      },
      domProps: {
        "value": items.Num
      },
      on: {
        "keypress": _vm.isNumber,
        "keydown": function($event) {
          if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
          $event.preventDefault();
        },
        "change": _vm.saveDeviceConfig
      }
    })]), _vm._v(" "), _c('div', {
      staticStyle: {
        "height": "15px"
      }
    })])
  }), _vm._v(" "), _c('p')], 2)])]), _vm._v(" "), _c('li', [_c('i', {
    staticClass: "fa fa-cog"
  }), _vm._v(" "), _c('div', {
    staticClass: "timeline-item"
  }, [_c('h3', {
    staticClass: "timeline-header"
  }, [_vm._v("VPN Settings                   \n                       "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.vpnEnablechekbox),
      expression: "vpnEnablechekbox"
    }],
    attrs: {
      "type": "checkbox",
      "id": "vpnEnablechekbox"
    },
    domProps: {
      "checked": Array.isArray(_vm.vpnEnablechekbox) ? _vm._i(_vm.vpnEnablechekbox, null) > -1 : (_vm.vpnEnablechekbox)
    },
    on: {
      "change": function($event) {
        var $$a = _vm.vpnEnablechekbox,
          $$el = $event.target,
          $$c = $$el.checked ? (true) : (false);
        if (Array.isArray($$a)) {
          var $$v = null,
            $$i = _vm._i($$a, $$v);
          if ($$el.checked) {
            $$i < 0 && (_vm.vpnEnablechekbox = $$a.concat([$$v]))
          } else {
            $$i > -1 && (_vm.vpnEnablechekbox = $$a.slice(0, $$i).concat($$a.slice($$i + 1)))
          }
        } else {
          _vm.vpnEnablechekbox = $$c
        }
      }
    }
  }), _vm._v(" "), _c('label', {
    staticClass: "inputcheckTEXTLBLcss",
    attrs: {
      "for": "vpnEnablechekbox"
    }
  }, [_vm._v("Enable ")]), _vm._v("              \n                         "), _c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("VPN Type : ")]), _vm._v("   \n                        "), _c('select', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.vpntypeTXT),
      expression: "vpntypeTXT"
    }],
    staticClass: "inputTEXTcss",
    staticStyle: {
      "width": "15%",
      "color": "#000"
    },
    attrs: {
      "name": "vpntypeTXT",
      "id": "vpntypeTXT",
      "disabled": !_vm.vpnEnablechekbox
    },
    on: {
      "change": function($event) {
        var $$selectedVal = Array.prototype.filter.call($event.target.options, function(o) {
          return o.selected
        }).map(function(o) {
          var val = "_value" in o ? o._value : o.value;
          return val
        });
        _vm.vpntypeTXT = $event.target.multiple ? $$selectedVal : $$selectedVal[0]
      }
    }
  }, [_c('option', {
    attrs: {
      "value": "IPSEC",
      "selected": ""
    }
  }, [_vm._v("IPSEC")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "PPTP"
    }
  }, [_vm._v("PPTP")])])]), _vm._v(" "), _c('div', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (_vm.vpntypeTXT == 'IPSEC'),
      expression: "vpntypeTXT == 'IPSEC'"
    }],
    staticClass: "timeline-body"
  }, [_c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Tunnel Name : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.vpnTunnalNameTXT),
      expression: "vpnTunnalNameTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "vpnTunnalNameTXT",
      "placeholder": "Tunnel Name",
      "maxlength": "32",
      "disabled": !_vm.vpnEnablechekbox
    },
    domProps: {
      "value": (_vm.vpnTunnalNameTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.vpnTunnalNameTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Pre Shared Key : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.vpnPreSharedKeyTXT),
      expression: "vpnPreSharedKeyTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "vpnPreSharedKeyTXT",
      "placeholder": "Pre Shared Key",
      "maxlength": "32",
      "disabled": !_vm.vpnEnablechekbox
    },
    domProps: {
      "value": (_vm.vpnPreSharedKeyTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.vpnPreSharedKeyTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Key Life Time : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.vpnKeyLifeTimeTXT),
      expression: "vpnKeyLifeTimeTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "vpnKeyLifeTimeTXT",
      "placeholder": "Key Life Time",
      "maxlength": "32",
      "disabled": !_vm.vpnEnablechekbox
    },
    domProps: {
      "value": (_vm.vpnKeyLifeTimeTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.vpnKeyLifeTimeTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Right Ip : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.vpnRightIpTXT),
      expression: "vpnRightIpTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "vpnRightIpTXT",
      "placeholder": "Right Ip",
      "maxlength": "32",
      "disabled": !_vm.vpnEnablechekbox
    },
    domProps: {
      "value": (_vm.vpnRightIpTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.vpnRightIpTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Right Subnet : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.vpnRightSubnetTXT),
      expression: "vpnRightSubnetTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "vpnRightSubnetTXT",
      "placeholder": "Right Subnet",
      "maxlength": "32",
      "disabled": !_vm.vpnEnablechekbox
    },
    domProps: {
      "value": (_vm.vpnRightSubnetTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.vpnRightSubnetTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Right Id : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.vpnRightIdTXT),
      expression: "vpnRightIdTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "vpnRightIdTXT",
      "placeholder": "Right Id",
      "maxlength": "32",
      "disabled": !_vm.vpnEnablechekbox
    },
    domProps: {
      "value": (_vm.vpnRightIdTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.vpnRightIdTXT = $event.target.value
      }
    }
  })])]), _vm._v(" "), _c('div', {
    staticStyle: {
      "height": "10px"
    }
  }), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Left Subnet : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.vpnLeftSubnetTXT),
      expression: "vpnLeftSubnetTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "vpnLeftSubnetTXT",
      "placeholder": "Left Subnet",
      "maxlength": "32",
      "disabled": !_vm.vpnEnablechekbox
    },
    domProps: {
      "value": (_vm.vpnLeftSubnetTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.vpnLeftSubnetTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Left Id : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.vpnLeftIdTXT),
      expression: "vpnLeftIdTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "vpnLeftIdTXT",
      "placeholder": "Left Id",
      "maxlength": "32",
      "disabled": !_vm.vpnEnablechekbox
    },
    domProps: {
      "value": (_vm.vpnLeftIdTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.vpnLeftIdTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Pfs : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.vpnPfsTXT),
      expression: "vpnPfsTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "vpnPfsTXT",
      "placeholder": "Pfs",
      "maxlength": "32",
      "disabled": !_vm.vpnEnablechekbox
    },
    domProps: {
      "value": (_vm.vpnPfsTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.vpnPfsTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("AggrMode : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.vpnAggrModeTXT),
      expression: "vpnAggrModeTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "vpnAggrModeTXT",
      "placeholder": "AggrMode",
      "maxlength": "32",
      "disabled": !_vm.vpnEnablechekbox
    },
    domProps: {
      "value": (_vm.vpnAggrModeTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.vpnAggrModeTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Keying Mode : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.VpnKeyingModeTXT),
      expression: "VpnKeyingModeTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "VpnKeyingModeTXT",
      "placeholder": "Keying Mode",
      "maxlength": "32",
      "disabled": !_vm.vpnEnablechekbox
    },
    domProps: {
      "value": (_vm.VpnKeyingModeTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.VpnKeyingModeTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Nat Trav : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.vpnNatTravTXT),
      expression: "vpnNatTravTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "vpnNatTravTXT",
      "placeholder": "Nat Trav",
      "maxlength": "32",
      "disabled": !_vm.vpnEnablechekbox
    },
    domProps: {
      "value": (_vm.vpnNatTravTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.vpnNatTravTXT = $event.target.value
      }
    }
  })])]), _vm._v(" "), _c('div', {
    staticStyle: {
      "height": "10px"
    }
  }), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("DhGrp : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.vpnDhGrpTXT),
      expression: "vpnDhGrpTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "vpnDhGrpTXT",
      "placeholder": "DhGrp",
      "maxlength": "32",
      "disabled": !_vm.vpnEnablechekbox
    },
    domProps: {
      "value": (_vm.vpnDhGrpTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.vpnDhGrpTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Encrpt : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.vpnEncrptTXT),
      expression: "vpnEncrptTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "vpnEncrptTXT",
      "placeholder": "Encrpt",
      "maxlength": "32",
      "disabled": !_vm.vpnEnablechekbox
    },
    domProps: {
      "value": (_vm.vpnEncrptTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.vpnEncrptTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Authen : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.vpnAuthenTXT),
      expression: "vpnAuthenTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "vpnAuthenTXT",
      "placeholder": "Authen",
      "maxlength": "32",
      "disabled": !_vm.vpnEnablechekbox
    },
    domProps: {
      "value": (_vm.vpnAuthenTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.vpnAuthenTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("DhGrp2 : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.vpnDhGrp2TXT),
      expression: "vpnDhGrp2TXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "vpnDhGrp2TXT",
      "placeholder": "DhGrp2",
      "maxlength": "32",
      "disabled": !_vm.vpnEnablechekbox
    },
    domProps: {
      "value": (_vm.vpnDhGrp2TXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.vpnDhGrp2TXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Encrpt2 : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.vpnEncrpt2TXT),
      expression: "vpnEncrpt2TXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "vpnEncrpt2TXT",
      "placeholder": "Encrpt2",
      "maxlength": "32",
      "disabled": !_vm.vpnEnablechekbox
    },
    domProps: {
      "value": (_vm.vpnEncrpt2TXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.vpnEncrpt2TXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Authen2 : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.vpnAuthen2TXT),
      expression: "vpnAuthen2TXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "vpnAuthen2TXT",
      "placeholder": "Authen2",
      "maxlength": "32",
      "disabled": !_vm.vpnEnablechekbox
    },
    domProps: {
      "value": (_vm.vpnAuthen2TXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.vpnAuthen2TXT = $event.target.value
      }
    }
  })])]), _vm._v(" "), _c('div', {
    staticStyle: {
      "height": "15px"
    }
  })]), _vm._v(" "), _c('div', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (_vm.vpntypeTXT == 'PPTP'),
      expression: "vpntypeTXT == 'PPTP'"
    }],
    staticClass: "timeline-body"
  }, [_c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Conn Name : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.vpnConnNameTXT),
      expression: "vpnConnNameTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "vpnConnNameTXT",
      "placeholder": "Conn Name",
      "maxlength": "32",
      "disabled": !_vm.vpnEnablechekbox
    },
    domProps: {
      "value": (_vm.vpnConnNameTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.vpnConnNameTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Local UName : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.vpnLocalUNameTXT),
      expression: "vpnLocalUNameTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "vpnLocalUNameTXT",
      "placeholder": "Local UName",
      "maxlength": "32",
      "disabled": !_vm.vpnEnablechekbox
    },
    domProps: {
      "value": (_vm.vpnLocalUNameTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.vpnLocalUNameTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Local Pwd : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.vpnLocalPwdTXT),
      expression: "vpnLocalPwdTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "vpnLocalPwdTXT",
      "placeholder": "Local Pwd",
      "maxlength": "32",
      "disabled": !_vm.vpnEnablechekbox
    },
    domProps: {
      "value": (_vm.vpnLocalPwdTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.vpnLocalPwdTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Rem Ip : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.vpnRemIpTXT),
      expression: "vpnRemIpTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "vpnRemIpTXT",
      "placeholder": "Rem Ip",
      "maxlength": "32",
      "disabled": !_vm.vpnEnablechekbox
    },
    domProps: {
      "value": (_vm.vpnRemIpTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.vpnRemIpTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("RemUName : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.vpnRemUNameTXT),
      expression: "vpnRemUNameTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "vpnRemUNameTXT",
      "placeholder": "RemUName",
      "maxlength": "32",
      "disabled": !_vm.vpnEnablechekbox
    },
    domProps: {
      "value": (_vm.vpnRemUNameTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.vpnRemUNameTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Req_mmpe128 : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.vpnReq_mmpe128TXT),
      expression: "vpnReq_mmpe128TXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "vpnReq_mmpe128TXT",
      "placeholder": "Req_mmpe128",
      "maxlength": "32",
      "disabled": !_vm.vpnEnablechekbox
    },
    domProps: {
      "value": (_vm.vpnReq_mmpe128TXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.vpnReq_mmpe128TXT = $event.target.value
      }
    }
  })])])])])]), _vm._v(" "), _c('li', [_c('i', {
    staticClass: "fa fa-cog"
  }), _vm._v(" "), _c('div', {
    staticClass: "timeline-item"
  }, [_c('h3', {
    staticClass: "timeline-header"
  }, [_vm._v("NTP Settings")]), _vm._v(" "), _c('div', {
    staticClass: "timeline-body"
  }, [_c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-5 text-center"
  }, [_vm._m(2), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-2",
    staticStyle: {
      "margin-top": "25px"
    }
  }, [_c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.ntpStatedwnTXT1chekbox),
      expression: "ntpStatedwnTXT1chekbox"
    }],
    attrs: {
      "type": "checkbox",
      "id": "ntpStatedwnTXT1chekbox"
    },
    domProps: {
      "checked": Array.isArray(_vm.ntpStatedwnTXT1chekbox) ? _vm._i(_vm.ntpStatedwnTXT1chekbox, null) > -1 : (_vm.ntpStatedwnTXT1chekbox)
    },
    on: {
      "change": function($event) {
        var $$a = _vm.ntpStatedwnTXT1chekbox,
          $$el = $event.target,
          $$c = $$el.checked ? (true) : (false);
        if (Array.isArray($$a)) {
          var $$v = null,
            $$i = _vm._i($$a, $$v);
          if ($$el.checked) {
            $$i < 0 && (_vm.ntpStatedwnTXT1chekbox = $$a.concat([$$v]))
          } else {
            $$i > -1 && (_vm.ntpStatedwnTXT1chekbox = $$a.slice(0, $$i).concat($$a.slice($$i + 1)))
          }
        } else {
          _vm.ntpStatedwnTXT1chekbox = $$c
        }
      }
    }
  }), _vm._v(" "), _c('label', {
    staticClass: "inputcheckTEXTLBLcss",
    attrs: {
      "for": "ntpStatedwnTXT1chekbox"
    }
  }, [_vm._v("Enable ")])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-5"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("IP Address : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.ntpserverIPAddressTXT1),
      expression: "ntpserverIPAddressTXT1"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "ntpserverIPAddressTXT1",
      "placeholder": "Server 1 IP Address",
      "maxlength": "32",
      "disabled": !_vm.ntpStatedwnTXT1chekbox
    },
    domProps: {
      "value": (_vm.ntpserverIPAddressTXT1)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.ntpserverIPAddressTXT1 = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-5"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Port :              ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.ntpserverPortTXT1),
      expression: "ntpserverPortTXT1"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "ntpserverPortTXT1",
      "placeholder": "Server 1 Port",
      "maxlength": "5",
      "disabled": !_vm.ntpStatedwnTXT1chekbox
    },
    domProps: {
      "value": (_vm.ntpserverPortTXT1)
    },
    on: {
      "keypress": _vm.isNumber,
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.ntpserverPortTXT1 = $event.target.value
      }
    }
  })])])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-5 text-center",
    staticStyle: {
      "border": "1px solid transparent",
      "border-left-color": "#0073b7"
    }
  }, [_vm._m(3), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-2",
    staticStyle: {
      "margin-top": "25px"
    }
  }, [_c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.ntpStatedwnTXT2chekbox),
      expression: "ntpStatedwnTXT2chekbox"
    }],
    attrs: {
      "type": "checkbox",
      "id": "ntpStatedwnTXT2chekbox"
    },
    domProps: {
      "checked": Array.isArray(_vm.ntpStatedwnTXT2chekbox) ? _vm._i(_vm.ntpStatedwnTXT2chekbox, null) > -1 : (_vm.ntpStatedwnTXT2chekbox)
    },
    on: {
      "change": function($event) {
        var $$a = _vm.ntpStatedwnTXT2chekbox,
          $$el = $event.target,
          $$c = $$el.checked ? (true) : (false);
        if (Array.isArray($$a)) {
          var $$v = null,
            $$i = _vm._i($$a, $$v);
          if ($$el.checked) {
            $$i < 0 && (_vm.ntpStatedwnTXT2chekbox = $$a.concat([$$v]))
          } else {
            $$i > -1 && (_vm.ntpStatedwnTXT2chekbox = $$a.slice(0, $$i).concat($$a.slice($$i + 1)))
          }
        } else {
          _vm.ntpStatedwnTXT2chekbox = $$c
        }
      }
    }
  }), _vm._v(" "), _c('label', {
    staticClass: "inputcheckTEXTLBLcss",
    attrs: {
      "for": "ntpStatedwnTXT2chekbox"
    }
  }, [_vm._v("Enable ")])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-5"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("IP Address : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.ntpserverIPAddressTXT2),
      expression: "ntpserverIPAddressTXT2"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "ntpserverIPAddressTXT2",
      "placeholder": "Server 2 IP Address",
      "maxlength": "32",
      "disabled": !_vm.ntpStatedwnTXT2chekbox
    },
    domProps: {
      "value": (_vm.ntpserverIPAddressTXT2)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.ntpserverIPAddressTXT2 = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-5"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Port :              ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.ntpserverPortTXT2),
      expression: "ntpserverPortTXT2"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "ntpserverPortTXT2",
      "placeholder": "Server 2 Port",
      "maxlength": "5",
      "disabled": !_vm.ntpStatedwnTXT2chekbox
    },
    domProps: {
      "value": (_vm.ntpserverPortTXT2)
    },
    on: {
      "keypress": _vm.isNumber,
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.ntpserverPortTXT2 = $event.target.value
      }
    }
  })])])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2",
    staticStyle: {
      "border": "1px solid transparent",
      "border-left-color": "#0073b7"
    }
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("  ")]), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-12"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("NTP Interval(in sec) : ")]), _vm._v(" "), _c('select', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.ntpserverIntervalTXT),
      expression: "ntpserverIntervalTXT"
    }],
    staticClass: "inputTEXTcss",
    staticStyle: {
      "width": "100%",
      "color": "#000"
    },
    attrs: {
      "name": "ntpserverIntervalTXT",
      "id": "ntpserverIntervalTXT",
      "disabled": !_vm.ntpStatedwnTXT1chekbox && !_vm.ntpStatedwnTXT2chekbox
    },
    on: {
      "change": function($event) {
        var $$selectedVal = Array.prototype.filter.call($event.target.options, function(o) {
          return o.selected
        }).map(function(o) {
          var val = "_value" in o ? o._value : o.value;
          return val
        });
        _vm.ntpserverIntervalTXT = $event.target.multiple ? $$selectedVal : $$selectedVal[0]
      }
    }
  }, [_c('option', {
    attrs: {
      "value": "choose ntp interval",
      "selected": ""
    }
  }, [_vm._v("choose ntp interval")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "15"
    }
  }, [_vm._v("15")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "30"
    }
  }, [_vm._v("30")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "45"
    }
  }, [_vm._v("45")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "60"
    }
  }, [_vm._v("60")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "120"
    }
  }, [_vm._v("120")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "240"
    }
  }, [_vm._v("240")])])])])])]), _vm._v(" "), _c('p')])])])])])])], 1)
},staticRenderFns: [function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('h5', [_c('b', [_vm._v("Ethernet -1 Configuration")])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('h5', [_c('b', [_vm._v("Ethernet -2 Configuration")])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('span', {
    staticClass: "inputTEXTLBLcss ",
    staticStyle: {
      "text-decoration": "underline"
    }
  }, [_c('i', {
    staticClass: "fa fa-desktop text-blue"
  }), _vm._v(" "), _c('b', [_vm._v("Server 1")])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('span', {
    staticClass: "inputTEXTLBLcss",
    staticStyle: {
      "text-decoration": "underline"
    }
  }, [_c('i', {
    staticClass: "fa fa-desktop text-blue"
  }), _vm._v(" "), _c('b', [_vm._v("Server 2")])])
}]}

/***/ }),
/* 126 */
/***/ (function(module, exports) {

module.exports={render:function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('footer', {
    staticClass: "main-footer"
  }, [_c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-4 text-left"
  }, [_c('span', [_vm._v(" © " + _vm._s(_vm.year) + ", Creative Micro System ")]), _vm._v(" "), _c('a', {
    attrs: {
      "href": "https://www.cmsgp.com",
      "target": "_blank"
    }
  }, [_vm._v(" - www.cmsgp.com")])]), _vm._v(" "), _vm._m(0), _vm._v(" "), _vm._m(1)])])
},staticRenderFns: [function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('div', {
    staticClass: "col-lg-4 text-center"
  }, [_c('span', [_vm._v("Product Support: +91-97419-66060 E-mail: support@cmsgp.com")])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('div', {
    staticClass: "col-lg-4 text-right"
  }, [_c('span', [_vm._v("Product Enquiries: +91-9686703878 E-mail: sales@cmsgp.com")])])
}]}

/***/ }),
/* 127 */
/***/ (function(module, exports) {

module.exports={render:function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('li', {
    staticClass: "notification-item"
  }, [_c('a', {
    attrs: {
      "href": "javascript:;"
    }
  }, [_c('h4', [_c('span', [_vm._v(_vm._s(_vm.notification.title))]), _vm._v(" "), _c('small', {
    staticClass: "time pull-right"
  }, [_c('i', {
    staticClass: "fa fa-clock-o"
  }), _vm._v(" "), _c('span', [_vm._v(_vm._s(_vm.notification.createdAt))])])]), _vm._v(" "), _c('p', [_vm._v(_vm._s(_vm.notification.body))])])])
},staticRenderFns: []}

/***/ }),
/* 128 */
/***/ (function(module, exports) {

module.exports={render:function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('section', {
    staticClass: "content",
    attrs: {
      "id": "uploadFirmwarepane"
    }
  }, [_c('vue-element-loading', {
    attrs: {
      "active": _vm.isLoading,
      "spinner": "spinner",
      "color": "#000",
      "is-full-screen": true
    }
  }), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-12"
  }, [_c('ul', {
    staticClass: "timeline"
  }, [_c('li', [_c('i', {
    staticClass: "fa fa-yelp bg-yellow"
  }), _vm._v(" "), _c('div', {
    staticClass: "timeline-item"
  }, [_c('span', {
    staticClass: "time"
  }, [_vm._v(" ")]), _vm._v(" "), _c('h3', {
    staticClass: "timeline-header"
  }, [_vm._v("\t ")]), _vm._v(" "), _c('div', {
    staticClass: "timeline-body"
  }, [_c('div', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (false),
      expression: "false"
    }],
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-3"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Serial No : ")]), _vm._v(" "), _c('input', {
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "serialNUMval",
      "disabled": ""
    }
  }), _vm._v(" "), _c('p'), _vm._v(" "), _c('button', {
    staticClass: "btn btn-default btn-md",
    attrs: {
      "type": "submit",
      "id": "serviceHistoryBTN"
    },
    on: {
      "click": _vm.viewServiceMethod
    }
  }, [_c('i', {
    staticClass: "fa fa-eye"
  }), _vm._v(" View Service history")]), _vm._v(" "), _c('button', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (false),
      expression: "false"
    }],
    staticClass: "btn btn-primary btn-md",
    attrs: {
      "type": "submit",
      "id": "addAdminBTN"
    },
    on: {
      "click": _vm.openAdminpopupMethod
    }
  }, [_c('i', {
    staticClass: "fa fa-user"
  }), _vm._v(" Admin")])]), _vm._v(" "), _vm._m(0)]), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-3"
  }, [_c('button', {
    staticClass: "btn btn-default btn-md",
    attrs: {
      "type": "submit",
      "id": "serviceHistoryBTN"
    },
    on: {
      "click": _vm.viewServiceMethod
    }
  }, [_c('i', {
    staticClass: "fa fa-eye"
  }), _vm._v(" View Service history")])])])])])])]), _vm._v(" "), _c('modal', {
    attrs: {
      "name": "adminLoginpopup",
      "transition": "nice-modal-fade",
      "classes": "demo-modal-class1",
      "min-width": 200,
      "min-height": 200,
      "pivot-y": 0.5,
      "adaptive": true,
      "draggable": true,
      "scrollable": true,
      "reset": true,
      "width": "30%",
      "height": "auto",
      "clickToClose": false
    },
    on: {
      "before-open": _vm.beforeOpen,
      "opened": _vm.opened,
      "closed": _vm.closed,
      "before-close": _vm.beforeClose
    }
  }, [_c('div', {
    staticClass: "size-modal-content"
  }, [_c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "modal-header"
  }, [_c('div', {
    staticClass: "col-lg-6",
    staticStyle: {
      "margin-top": "-20px"
    }
  }, [_c('h4', {
    staticClass: "heading",
    staticStyle: {
      "color": "#5e72e4"
    }
  }, [_vm._v(" Service Login")])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-6 text-right",
    staticStyle: {
      "margin-top": "-20px"
    }
  }, [_c('button', {
    staticClass: "btn btn-default",
    staticStyle: {
      "background": "transparent",
      "border": "1px solid transparent"
    },
    attrs: {
      "id": "save_closeBTN",
      "type": "button"
    },
    on: {
      "click": _vm.adminLoginpopupclose
    }
  }, [_c('span', {
    staticClass: "white-text",
    attrs: {
      "aria-hidden": "true"
    }
  }, [_vm._v("×")])])])])]), _vm._v(" "), _c('div', {
    staticClass: "modal-body",
    staticStyle: {
      "margin-top": "-8px"
    }
  }, [_c('p', [_vm._v(" ")]), _vm._v(" "), [_c('form', {
    staticStyle: {
      "padding-left": "0px !important",
      "padding-right": "0px !important"
    }
  }, [_c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-12"
  }, [_c('span', [_vm._v("User Name : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.adminusernameTXT),
      expression: "adminusernameTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "adminusernameTXTid",
      "type": "text",
      "placeholder": "Enter user name"
    },
    domProps: {
      "value": (_vm.adminusernameTXT)
    },
    on: {
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.adminusernameTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-12"
  }), _vm._v(" "), _c('div', {
    staticClass: "col-lg-12"
  }), _vm._v(" "), _c('div', {
    staticClass: "col-lg-12"
  }), _vm._v(" "), _c('div', {
    staticClass: "col-lg-12"
  }), _vm._v(" "), _c('div', {
    staticClass: "col-lg-12"
  }), _vm._v(" "), _c('div', {
    staticClass: "col-lg-12"
  }), _vm._v(" "), _c('div', {
    staticClass: "col-lg-12"
  }, [_c('span', [_vm._v("Password : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.adminpasswordTXT),
      expression: "adminpasswordTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "adminpasswordTXTid",
      "type": "password",
      "placeholder": "Enter password"
    },
    domProps: {
      "value": (_vm.adminpasswordTXT)
    },
    on: {
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.adminpasswordTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-12"
  }), _c('div', {
    staticClass: "col-lg-12"
  }), _c('div', {
    staticClass: "col-lg-12"
  }), _c('div', {
    staticClass: "col-lg-12"
  }), _c('div', {
    staticClass: "col-lg-12"
  }), _vm._v(" "), _c('div', {
    staticClass: "col-lg-12"
  }), _c('div', {
    staticClass: "col-lg-12"
  }), _c('div', {
    staticClass: "col-lg-12"
  }), _c('div', {
    staticClass: "col-lg-12"
  }), _vm._v(" "), _c('div', {
    staticClass: "col-lg-12"
  }, [_c('button', {
    staticClass: "btn btn-md btn-primary",
    attrs: {
      "type": "submit"
    },
    on: {
      "click": _vm.adminLoginMethod
    }
  }, [_vm._v("Login")])])])])]], 2), _vm._v(" "), _c('div', {
    staticClass: "modal-footer flex-center"
  })])]), _vm._v(" "), _c('modal', {
    attrs: {
      "name": "addAdmindescriptionPopup",
      "transition": "nice-modal-fade",
      "classes": "demo-modal-class1",
      "min-width": 200,
      "min-height": 200,
      "pivot-y": 0.5,
      "adaptive": true,
      "draggable": true,
      "scrollable": true,
      "reset": true,
      "width": "55%",
      "height": "auto",
      "clickToClose": false
    },
    on: {
      "before-open": _vm.beforeOpen,
      "opened": _vm.opened,
      "closed": _vm.closed,
      "before-close": _vm.beforeClose
    }
  }, [_c('div', {
    staticClass: "size-modal-content"
  }, [_c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "modal-header"
  }, [_c('div', {
    staticClass: "col-lg-6",
    staticStyle: {
      "margin-top": "-20px"
    }
  }, [_c('h4', {
    staticClass: "heading",
    staticStyle: {
      "color": "#5e72e4"
    }
  }, [_vm._v(" Add Service History ")])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-6 text-right",
    staticStyle: {
      "margin-top": "-20px"
    }
  }, [_c('button', {
    staticClass: "btn btn-default",
    staticStyle: {
      "background": "transparent",
      "border": "1px solid transparent"
    },
    attrs: {
      "id": "save_closeBTN",
      "type": "button"
    },
    on: {
      "click": _vm.addAdmindescriptionPopupclose
    }
  }, [_c('span', {
    staticClass: "white-text",
    attrs: {
      "aria-hidden": "true"
    }
  }, [_vm._v("×")])])])])]), _vm._v(" "), _c('div', {
    staticClass: "modal-body",
    staticStyle: {
      "margin-top": "-8px"
    }
  }, [_c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-10 text-left"
  }), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2 text-right"
  }, [_c('button', {
    staticClass: "btn btn-sm btn-primary pull-right",
    staticStyle: {
      "margin-top": "-5px",
      "margin-right": "0px"
    },
    attrs: {
      "id": "adddesrowBtn",
      "title": "Add Description"
    },
    on: {
      "click": function($event) {
        $event.preventDefault();
        return _vm.adddesrowMethod($event)
      }
    }
  }, [_c('img', {
    attrs: {
      "src": "/static/img/images/add.png"
    }
  }), _vm._v(" Add Items\n          ")])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-12"
  }, [
    [_c('div', {
      staticClass: "table-responsive",
      staticStyle: {
        "margin-top": "2px",
        "border": "1px solid lightgray"
      },
      style: ({
        height: _vm.admindescripSAVEHeightData + 120 + 'px'
      }),
      attrs: {
        "id": "adminDescrpPANE"
      }
    }, [_c('table', {
      staticClass: "table table-bordered table-striped table-responsive-stack",
      staticStyle: {
        "text-align": "center"
      },
      attrs: {
        "id": "adminDescrpPANETableID"
      }
    }, [_c('thead', {
      staticStyle: {
        "position": "sticky",
        "top": "-1px",
        "z-index": "1"
      }
    }, [_c('tr', [_c('th', {
      staticStyle: {
        "width": "50px"
      }
    }, [_vm._v("S.No")]), _vm._v(" "), _c('th', {
      staticStyle: {
        "width": "50px"
      }
    }, [_vm._v("Date")]), _vm._v(" "), _c('th', [_vm._v("Service Description")]), _vm._v(" "), _c('th', {
      staticStyle: {
        "width": "200px"
      }
    }, [_vm._v("Person Name")]), _vm._v(" "), _c('th', {
      staticStyle: {
        "width": "50px"
      }
    }, [_vm._v("delete")])])]), _vm._v(" "), _c('tbody', _vm._l((_vm.adminDesArray), function(adminItems, indx) {
      return _c('tr', {
        key: indx
      }, [_c('td', {
        staticStyle: {
          "width": "50px",
          "vertical-align": "middle"
        }
      }, [_c('span', [_vm._v(_vm._s(indx + 1))])]), _vm._v(" "), _c('td', {
        staticStyle: {
          "width": "50px",
          "vertical-align": "middle"
        }
      }, [_vm._v(_vm._s(adminItems.date))]), _vm._v(" "), _c('td', [_c('input', {
        staticClass: "inputTEXTcss",
        attrs: {
          "id": 'descTXTid' + indx,
          "type": "textarea",
          "placeholder": "enter service description"
        },
        domProps: {
          "value": adminItems.description
        },
        on: {
          "change": function($event) {
            return _vm.changeDecsTextareaFunction(indx)
          }
        }
      })]), _vm._v(" "), _c('td', {
        staticStyle: {
          "width": "200px"
        }
      }, [_c('input', {
        staticClass: "inputTEXTcss",
        attrs: {
          "type": "text",
          "id": 'personTXTid' + indx,
          "placeholder": "enter person name"
        },
        domProps: {
          "value": adminItems.person
        },
        on: {
          "change": function($event) {
            return _vm.changepersonTextFunction(indx)
          }
        }
      })]), _vm._v(" "), _c('td', {
        staticStyle: {
          "width": "50px"
        }
      }, [_c('img', {
        attrs: {
          "id": 'admindescDeleteBTN' + indx,
          "src": "/static/img/images/delete.png",
          "title": "Delete Register"
        },
        on: {
          "click": function($event) {
            $event.preventDefault();
            return _vm.admindescDeleteBTNFunction(indx)
          }
        }
      })])])
    }), 0)])])]
  ], 2)])]), _vm._v(" "), _c('div', {
    staticClass: "modal-footer flex-center"
  }, [_c('a', {
    staticClass: "btn btn-primary btnPadding",
    staticStyle: {
      "color": "#fff"
    },
    attrs: {
      "id": "admindescSaveBTN"
    },
    on: {
      "click": _vm.addAdmindescriptionSAVEMethod
    }
  }, [_vm._v("Save")]), _vm._v(" "), _c('a', {
    staticClass: "btn btn-default waves-effect btnPadding",
    attrs: {
      "id": "addAdmindescriptionPopupBNT",
      "type": "button"
    },
    on: {
      "click": _vm.addAdmindescriptionPopupclose
    }
  }, [_vm._v("Cancel")])])])])], 1)])], 1)
},staticRenderFns: [function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('div', {
    staticClass: "col-lg-4"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Firmware Version : ")]), _vm._v(" "), _c('input', {
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "serialversionval",
      "disabled": ""
    }
  })])
}]}

/***/ }),
/* 129 */
/***/ (function(module, exports) {

module.exports={render:function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('section', {
    staticClass: "content",
    attrs: {
      "id": "changepassPage"
    }
  }, [_c('vue-element-loading', {
    attrs: {
      "active": _vm.isLoading,
      "spinner": "spinner",
      "color": "#000",
      "is-full-screen": true
    }
  }), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-12"
  }, [_c('ul', {
    staticClass: "timeline"
  }, [_c('li', [_c('i', {
    staticClass: "fa fa-key bg-yellow"
  }), _vm._v(" "), _c('div', {
    staticClass: "timeline-item"
  }, [_c('div', {
    staticClass: "timeline-body"
  }, [_c('div', {
    staticClass: "row"
  }, [_vm._m(0), _vm._v(" "), _c('div', {
    staticClass: "col-lg-4"
  }, [_c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.changeusernameTXT),
      expression: "changeusernameTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "changeusernameTXT",
      "placeholder": "User Name"
    },
    domProps: {
      "value": (_vm.changeusernameTXT)
    },
    on: {
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.changeusernameTXT = $event.target.value
      }
    }
  })])]), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_vm._m(1), _vm._v(" "), _c('div', {
    staticClass: "col-lg-4"
  }, [_c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.changecurrpassTXT),
      expression: "changecurrpassTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "changecurrpassTXT",
      "placeholder": "Current Password"
    },
    domProps: {
      "value": (_vm.changecurrpassTXT)
    },
    on: {
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.changecurrpassTXT = $event.target.value
      }
    }
  })])]), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_vm._m(2), _vm._v(" "), _c('div', {
    staticClass: "col-lg-4"
  }, [_c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.changenewpassTXT),
      expression: "changenewpassTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "changenewpassTXT",
      "placeholder": "New Password"
    },
    domProps: {
      "value": (_vm.changenewpassTXT)
    },
    on: {
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.changenewpassTXT = $event.target.value
      }
    }
  })])]), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_vm._m(3), _vm._v(" "), _c('div', {
    staticClass: "col-lg-4"
  }, [_c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.changeconfrimPassTXT),
      expression: "changeconfrimPassTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "changeconfrimPassTXT",
      "placeholder": "Confirm Password"
    },
    domProps: {
      "value": (_vm.changeconfrimPassTXT)
    },
    on: {
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.changeconfrimPassTXT = $event.target.value
      }
    }
  })])]), _vm._v(" "), _c('p'), _vm._v(" "), _vm._m(4)])])])])])])], 1)
},staticRenderFns: [function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("User Name :")])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Current Password :")])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("New Password :")])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Confirm Password :")])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-2"
  }), _vm._v(" "), _c('div', {
    staticClass: "col-lg-4"
  }, [_c('button', {
    staticClass: "btn btn-sm btn-default",
    attrs: {
      "id": "changePasssubmitBTN",
      "type": "button"
    }
  }, [_vm._v("\n                          Submit\n                    ")])])])
}]}

/***/ }),
/* 130 */
/***/ (function(module, exports) {

module.exports={render:function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('section', {
    staticClass: "content",
    attrs: {
      "id": "paramsconfigpane"
    }
  }, [_c('vue-element-loading', {
    attrs: {
      "active": _vm.isLoading,
      "spinner": "spinner",
      "color": "#000",
      "is-full-screen": true
    }
  }), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-12"
  }, [_c('ul', {
    staticClass: "timeline"
  }, [_c('li', [_c('i', {
    staticClass: "fa fa-star-half-o bg-yellow"
  }), _vm._v(" "), _c('div', {
    staticClass: "timeline-item"
  }, [_c('div', {
    staticClass: "timeline-body"
  }, [_c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-12"
  }, [_vm._m(0), _vm._v(" "), _c('div', {
    staticClass: "tab-content"
  }, [_c('div', {
    staticClass: "tab-pane active",
    attrs: {
      "role": "tabpanel",
      "aria-labelledby": "paramTab1PANE",
      "id": "paramTab1PANE"
    }
  }, [_c('p'), _vm._v(" "), _c('h4', {
    staticClass: "timeline-header",
    staticStyle: {
      "text-decoration": "underline",
      "color": "#0073b7"
    }
  }, [_vm._v(" Instantaneous Parameter Configuration:")]), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-3"
  }, [_c('h4', {
    staticClass: "text-center",
    staticStyle: {
      "background": "#1a495e",
      "color": "white",
      "height": "30px",
      "padding-top": "5px"
    }
  }, [_vm._v("Master Parameter List ")]), _vm._v(" "), _c('ul', {
    staticStyle: {
      "border": "1px solid lightgray",
      "overflow": "scroll",
      "overflow-x": "hidden",
      "padding": "10px",
      "font-size": "15px"
    },
    style: ({
      height: _vm.instanListheight
    })
  }, _vm._l((_vm.instanMasterParamsList), function(paramsItems, instIndex) {
    return _c('li', {
      key: instIndex
    }, [_c('label', {
      staticStyle: {
        "font-weight": "normal"
      }
    }, [_c('input', {
      attrs: {
        "id": 'masterINSTCheckbox' + (instIndex + 1),
        "type": "checkbox"
      },
      on: {
        "click": function($event) {
          _vm.checkedmasterINSTfunction('masterINSTCheckbox' + (instIndex + 1), paramsItems)
        }
      }
    }), _vm._v("\n        " + _vm._s(paramsItems.obis) + " - " + _vm._s(paramsItems.def) + "\n      ")])])
  }), 0)]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-6"
  }, [_c('h4', {
    staticClass: "text-center",
    staticStyle: {
      "background": "#1a495e",
      "color": "white",
      "height": "30px",
      "padding-top": "5px"
    }
  }, [_vm._v("Selected Parameter List ")]), _vm._v(" "), [_c('div', {
    staticClass: "table-responsive",
    staticStyle: {
      "border": "1px solid lightgray"
    },
    style: ({
      height: _vm.instanListheight
    }),
    attrs: {
      "id": "selectINSTparamsTablePane"
    }
  }, [_c('table', {
    staticClass: "table table-bordered table-responsive-stack",
    attrs: {
      "id": "selectINSTparamsTBl"
    }
  }, [_vm._m(1), _vm._v(" "), (_vm.instanselectedParamsList.length != 0) ? _c('tbody', _vm._l((_vm.instanselectedParamsList), function(insttems, instindex) {
    return _c('tr', {
      key: instindex
    }, [_c('td', [_vm._v(_vm._s(instindex + 1))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(insttems.obis))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(insttems.def))]), _vm._v(" "), _c('td', [_c('input', {
      staticClass: "inputTEXTcss",
      attrs: {
        "type": "text",
        "id": 'instTXT' + (instindex + 1)
      },
      domProps: {
        "value": insttems.assign
      },
      on: {
        "change": function($event) {
          _vm.getINSTassignName(instindex, 'instTXT' + (instindex + 1))
        }
      }
    })])])
  }), 0) : _vm._e()]), _vm._v(" "), (_vm.instanselectedParamsList.length == 0) ? _c('div', {
    staticClass: "text-center text-block"
  }, [_c('span', [_vm._v("No Records Found")])]) : _vm._e()])]], 2)])]), _vm._v(" "), _c('div', {
    staticClass: "tab-pane",
    attrs: {
      "role": "tabpanel",
      "aria-labelledby": "paramTab2PANE",
      "id": "paramTab2PANE"
    }
  }, [_c('p'), _vm._v(" "), _c('h4', {
    staticClass: "timeline-header",
    staticStyle: {
      "text-decoration": "underline",
      "color": "#0073b7"
    }
  }, [_vm._v(" Load Survey Parameter Configuration:")]), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-3"
  }, [_c('h4', {
    staticClass: "text-center",
    staticStyle: {
      "background": "#1a495e",
      "color": "white",
      "height": "30px",
      "padding-top": "5px"
    }
  }, [_vm._v("Master Parameter List ")]), _vm._v(" "), _c('ul', {
    staticStyle: {
      "border": "1px solid lightgray",
      "overflow": "scroll",
      "overflow-x": "hidden",
      "padding": "10px",
      "font-size": "16px"
    },
    style: ({
      height: _vm.instanListheight
    })
  }, _vm._l((_vm.loadserveMasterParamsList), function(paramsItems, lsIndex) {
    return _c('li', {
      key: lsIndex
    }, [_c('label', {
      staticStyle: {
        "font-weight": "normal"
      }
    }, [_c('input', {
      attrs: {
        "id": 'masterLSCheckbox' + (lsIndex + 1),
        "type": "checkbox"
      },
      on: {
        "click": function($event) {
          _vm.checkedmasterLSfunction('masterLSCheckbox' + (lsIndex + 1), paramsItems)
        }
      }
    }), _vm._v("\n        " + _vm._s(paramsItems.obis) + " - " + _vm._s(paramsItems.def) + "\n      ")])])
  }), 0)]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-6"
  }, [_c('h4', {
    staticClass: "text-center",
    staticStyle: {
      "background": "#1a495e",
      "color": "white",
      "height": "30px",
      "padding-top": "5px"
    }
  }, [_vm._v("Selected Parameter List ")]), _vm._v(" "), [_c('div', {
    staticClass: "table-responsive",
    staticStyle: {
      "border": "1px solid lightgray"
    },
    style: ({
      height: _vm.instanListheight
    }),
    attrs: {
      "id": "selectLSparamsTablePane"
    }
  }, [_c('table', {
    staticClass: "table table-bordered table-responsive-stack",
    attrs: {
      "id": "selectLSparamsTBl"
    }
  }, [_vm._m(2), _vm._v(" "), (_vm.loadserveselectedParamsList.length != 0) ? _c('tbody', _vm._l((_vm.loadserveselectedParamsList), function(tems, lsindex) {
    return _c('tr', {
      key: lsindex
    }, [_c('td', [_vm._v(_vm._s(lsindex + 1))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(tems.obis))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(tems.def))]), _vm._v(" "), _c('td', [_c('input', {
      staticClass: "inputTEXTcss",
      attrs: {
        "type": "text",
        "id": 'loadsvyTXT' + (lsindex + 1)
      },
      domProps: {
        "value": tems.assign
      },
      on: {
        "change": function($event) {
          _vm.getLSassignName(lsindex, 'loadsvyTXT' + (lsindex + 1))
        }
      }
    })])])
  }), 0) : _vm._e()]), _vm._v(" "), (_vm.loadserveselectedParamsList.length == 0) ? _c('div', {
    staticClass: "text-center text-block"
  }, [_c('span', [_vm._v("No Records Found")])]) : _vm._e()])]], 2)])]), _vm._v(" "), _c('div', {
    staticClass: "tab-pane",
    attrs: {
      "role": "tabpanel",
      "aria-labelledby": "paramTab3PANE",
      "id": "paramTab3PANE"
    }
  }, [_c('p'), _vm._v(" "), _c('h4', {
    staticClass: "timeline-header",
    staticStyle: {
      "text-decoration": "underline",
      "color": "#0073b7"
    }
  }, [_vm._v(" Event Data Parameter Configuration:")]), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-3"
  }, [_c('h4', {
    staticClass: "text-center",
    staticStyle: {
      "background": "#1a495e",
      "color": "white",
      "height": "30px",
      "padding-top": "5px"
    }
  }, [_vm._v("Master Parameter List ")]), _vm._v(" "), _c('ul', {
    staticStyle: {
      "border": "1px solid lightgray",
      "overflow": "scroll",
      "overflow-x": "hidden",
      "padding": "10px",
      "font-size": "16px"
    },
    style: ({
      height: _vm.instanListheight
    })
  }, _vm._l((_vm.eventdataMasterParamsList), function(paramsItems, eventIndex) {
    return _c('li', {
      key: eventIndex
    }, [_c('label', {
      staticStyle: {
        "font-weight": "normal"
      }
    }, [_c('input', {
      attrs: {
        "id": 'masterEVENTCheckbox' + (eventIndex + 1),
        "type": "checkbox"
      },
      on: {
        "click": function($event) {
          _vm.checkedmasterEVENTfunction('masterEVENTCheckbox' + (eventIndex + 1), paramsItems)
        }
      }
    }), _vm._v("\n        " + _vm._s(paramsItems.obis) + " - " + _vm._s(paramsItems.def) + "\n      ")])])
  }), 0)]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-6"
  }, [_c('h4', {
    staticClass: "text-center",
    staticStyle: {
      "background": "#1a495e",
      "color": "white",
      "height": "30px",
      "padding-top": "5px"
    }
  }, [_vm._v("Selected Parameter List ")]), _vm._v(" "), [_c('div', {
    staticClass: "table-responsive",
    staticStyle: {
      "border": "1px solid lightgray"
    },
    style: ({
      height: _vm.instanListheight
    }),
    attrs: {
      "id": "selectEVENTparamsTablePane"
    }
  }, [_c('table', {
    staticClass: "table table-bordered table-responsive-stack",
    attrs: {
      "id": "selectEVENTparamsTBl"
    }
  }, [_vm._m(3), _vm._v(" "), (_vm.eventdataselectedParamsList.length != 0) ? _c('tbody', _vm._l((_vm.eventdataselectedParamsList), function(tems, eventindex) {
    return _c('tr', {
      key: eventindex
    }, [_c('td', [_vm._v(_vm._s(eventindex + 1))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(tems.obis))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(tems.def))]), _vm._v(" "), _c('td', [_c('input', {
      staticClass: "inputTEXTcss",
      attrs: {
        "type": "text",
        "id": 'eventdataTXT' + (eventindex + 1)
      },
      domProps: {
        "value": tems.assign
      },
      on: {
        "change": function($event) {
          _vm.getEVENTassignName(eventindex, 'eventdataTXT' + (eventindex + 1))
        }
      }
    })])])
  }), 0) : _vm._e()]), _vm._v(" "), (_vm.eventdataselectedParamsList.length == 0) ? _c('div', {
    staticClass: "text-center text-block"
  }, [_c('span', [_vm._v("No Records Found")])]) : _vm._e()])]], 2)])]), _vm._v(" "), _c('div', {
    staticClass: "tab-pane",
    attrs: {
      "role": "tabpanel",
      "aria-labelledby": "paramTab4PANE",
      "id": "paramTab4PANE"
    }
  }, [_c('p'), _vm._v(" "), _c('h4', {
    staticClass: "timeline-header",
    staticStyle: {
      "text-decoration": "underline",
      "color": "#0073b7"
    }
  }, [_vm._v(" Midnight Parameter Configuration:")]), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-3"
  }, [_c('h4', {
    staticClass: "text-center",
    staticStyle: {
      "background": "#1a495e",
      "color": "white",
      "height": "30px",
      "padding-top": "5px"
    }
  }, [_vm._v("Master Parameter List ")]), _vm._v(" "), _c('ul', {
    staticStyle: {
      "border": "1px solid lightgray",
      "overflow": "scroll",
      "overflow-x": "hidden",
      "padding": "10px",
      "font-size": "16px"
    },
    style: ({
      height: _vm.instanListheight
    })
  }, _vm._l((_vm.midnightMasterParamsList), function(paramsItems, mnIndex) {
    return _c('li', {
      key: mnIndex
    }, [_c('label', {
      staticStyle: {
        "font-weight": "normal"
      }
    }, [_c('input', {
      attrs: {
        "id": 'masterMNCheckbox' + (mnIndex + 1),
        "type": "checkbox"
      },
      on: {
        "click": function($event) {
          _vm.checkedmasterMNfunction('masterMNCheckbox' + (mnIndex + 1), paramsItems)
        }
      }
    }), _vm._v("\n        " + _vm._s(paramsItems.obis) + " - " + _vm._s(paramsItems.def) + "\n      ")])])
  }), 0)]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-6"
  }, [_c('h4', {
    staticClass: "text-center",
    staticStyle: {
      "background": "#1a495e",
      "color": "white",
      "height": "30px",
      "padding-top": "5px"
    }
  }, [_vm._v("Selected Parameter List ")]), _vm._v(" "), [_c('div', {
    staticClass: "table-responsive",
    staticStyle: {
      "border": "1px solid lightgray"
    },
    style: ({
      height: _vm.instanListheight
    }),
    attrs: {
      "id": "selectMNparamsTablePane"
    }
  }, [_c('table', {
    staticClass: "table table-bordered table-responsive-stack",
    attrs: {
      "id": "selectMNparamsTBl"
    }
  }, [_vm._m(4), _vm._v(" "), (_vm.midnightselectedParamsList.length != 0) ? _c('tbody', _vm._l((_vm.midnightselectedParamsList), function(tems, mmindex) {
    return _c('tr', {
      key: mmindex
    }, [_c('td', [_vm._v(_vm._s(mmindex + 1))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(tems.obis))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(tems.def))]), _vm._v(" "), _c('td', [_c('input', {
      staticClass: "inputTEXTcss",
      attrs: {
        "type": "text",
        "id": 'midnightselTXT' + (mmindex + 1)
      },
      domProps: {
        "value": tems.assign
      },
      on: {
        "change": function($event) {
          _vm.getMNassignName(mmindex, 'midnightselTXT' + (mmindex + 1))
        }
      }
    })])])
  }), 0) : _vm._e()]), _vm._v(" "), (_vm.midnightselectedParamsList.length == 0) ? _c('div', {
    staticClass: "text-center text-block"
  }, [_c('span', [_vm._v("No Records Found")])]) : _vm._e()])]], 2)])]), _vm._v(" "), _c('div', {
    staticClass: "tab-pane",
    attrs: {
      "role": "tabpanel",
      "aria-labelledby": "paramTab5PANE",
      "id": "paramTab5PANE"
    }
  }, [_c('p'), _vm._v(" "), _c('h4', {
    staticClass: "timeline-header",
    staticStyle: {
      "text-decoration": "underline",
      "color": "#0073b7"
    }
  }, [_vm._v(" Billing Parameter Configuration:")]), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-3"
  }, [_c('h4', {
    staticClass: "text-center",
    staticStyle: {
      "background": "#1a495e",
      "color": "white",
      "height": "30px",
      "padding-top": "5px"
    }
  }, [_vm._v("Master Parameter List ")]), _vm._v(" "), _c('ul', {
    staticStyle: {
      "border": "1px solid lightgray",
      "overflow": "scroll",
      "overflow-x": "hidden",
      "padding": "10px",
      "font-size": "16px"
    },
    style: ({
      height: _vm.instanListheight
    })
  }, _vm._l((_vm.billingMasterParamsList), function(paramsItems, billIndex) {
    return _c('li', {
      key: billIndex
    }, [_c('label', {
      staticStyle: {
        "font-weight": "normal"
      }
    }, [_c('input', {
      attrs: {
        "id": 'masterBILLCheckbox' + (billIndex + 1),
        "type": "checkbox"
      },
      on: {
        "click": function($event) {
          _vm.checkedmasterBILLfunction('masterBILLCheckbox' + (billIndex + 1), paramsItems)
        }
      }
    }), _vm._v("\n        " + _vm._s(paramsItems.obis) + " - " + _vm._s(paramsItems.def) + "\n      ")])])
  }), 0)]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-6"
  }, [_c('h4', {
    staticClass: "text-center",
    staticStyle: {
      "background": "#1a495e",
      "color": "white",
      "height": "30px",
      "padding-top": "5px"
    }
  }, [_vm._v("Selected Parameter List ")]), _vm._v(" "), [_c('div', {
    staticClass: "table-responsive",
    staticStyle: {
      "border": "1px solid lightgray"
    },
    style: ({
      height: _vm.instanListheight
    }),
    attrs: {
      "id": "selectBILLparamsTablePane"
    }
  }, [_c('table', {
    staticClass: "table table-bordered table-responsive-stack",
    attrs: {
      "id": "selectBILLparamsTBl"
    }
  }, [_vm._m(5), _vm._v(" "), (_vm.billingselectedParamsList.length != 0) ? _c('tbody', _vm._l((_vm.billingselectedParamsList), function(tems, billindex) {
    return _c('tr', {
      key: billindex
    }, [_c('td', [_vm._v(_vm._s(billindex + 1))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(tems.obis))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(tems.def))]), _vm._v(" "), _c('td', [_c('input', {
      staticClass: "inputTEXTcss",
      attrs: {
        "type": "text",
        "id": 'bilselTXT' + (billindex + 1)
      },
      domProps: {
        "value": tems.assign
      },
      on: {
        "change": function($event) {
          _vm.getBILLassignName(billindex, 'bilselTXT' + (billindex + 1))
        }
      }
    })])])
  }), 0) : _vm._e()]), _vm._v(" "), (_vm.billingselectedParamsList.length == 0) ? _c('div', {
    staticClass: "text-center text-block"
  }, [_c('span', [_vm._v("No Records Found")])]) : _vm._e()])]], 2)])])])])])])])])])])])], 1)
},staticRenderFns: [function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('div', {
    staticClass: "tab",
    attrs: {
      "role": "tabpanel"
    }
  }, [_c('ul', {
    staticClass: "nav nav-tabs",
    attrs: {
      "role": "tablist"
    }
  }, [_c('li', {
    staticClass: "active",
    attrs: {
      "role": "presentation",
      "id": "paramTab1"
    }
  }, [_c('a', {
    staticStyle: {
      "text-transform": "uppercase"
    },
    attrs: {
      "id": "paramTab1button",
      "href": "#paramTab1PANE",
      "aria-controls": "home",
      "role": "tab",
      "data-toggle": "tab"
    }
  }, [_c('i', {
    staticClass: "fa fa-th-large iconbg",
    attrs: {
      "aria-hidden": "true"
    }
  }), _vm._v("   Instantaneous\n                        ")])]), _vm._v(" "), _c('li', {
    attrs: {
      "role": "presentation",
      "id": "paramTab2"
    }
  }, [_c('a', {
    staticStyle: {
      "text-transform": "uppercase"
    },
    attrs: {
      "id": "paramTab2button",
      "href": "#paramTab2PANE",
      "aria-controls": "home",
      "role": "tab",
      "data-toggle": "tab"
    }
  }, [_c('i', {
    staticClass: "fa fa-th-large iconbg",
    attrs: {
      "aria-hidden": "true"
    }
  }), _vm._v("   Load Survey\n                        ")])]), _vm._v(" "), _c('li', {
    attrs: {
      "role": "presentation",
      "id": "paramTab3"
    }
  }, [_c('a', {
    staticStyle: {
      "text-transform": "uppercase"
    },
    attrs: {
      "id": "paramTab3button",
      "href": "#paramTab3PANE",
      "aria-controls": "home",
      "role": "tab",
      "data-toggle": "tab"
    }
  }, [_c('i', {
    staticClass: "fa fa-th-large iconbg",
    attrs: {
      "aria-hidden": "true"
    }
  }), _vm._v("   Event Data\n                        ")])]), _vm._v(" "), _c('li', {
    attrs: {
      "role": "presentation",
      "id": "paramTab4"
    }
  }, [_c('a', {
    staticStyle: {
      "text-transform": "uppercase"
    },
    attrs: {
      "id": "paramTab4button",
      "href": "#paramTab4PANE",
      "aria-controls": "home",
      "role": "tab",
      "data-toggle": "tab"
    }
  }, [_c('i', {
    staticClass: "fa fa-th-large iconbg",
    attrs: {
      "aria-hidden": "true"
    }
  }), _vm._v("   Midnight\n                        ")])]), _vm._v(" "), _c('li', {
    attrs: {
      "role": "presentation",
      "id": "paramTab5"
    }
  }, [_c('a', {
    staticStyle: {
      "text-transform": "uppercase"
    },
    attrs: {
      "id": "paramTab5button",
      "href": "#paramTab5PANE",
      "aria-controls": "home",
      "role": "tab",
      "data-toggle": "tab"
    }
  }, [_c('i', {
    staticClass: "fa fa-th-large iconbg",
    attrs: {
      "aria-hidden": "true"
    }
  }), _vm._v("   Billing\n                        ")])])])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('thead', {
    staticStyle: {
      "position": "sticky",
      "top": "-1px",
      "z-index": "1"
    }
  }, [_c('tr', [_c('th', {
    staticStyle: {
      "height": "25px !important"
    }
  }, [_vm._v("S.No")]), _vm._v(" "), _c('th', {
    staticStyle: {
      "height": "25px !important"
    }
  }, [_vm._v("OBIS Code")]), _vm._v(" "), _c('th', {
    staticStyle: {
      "height": "25px !important"
    }
  }, [_vm._v("Default Name")]), _vm._v(" "), _c('th', {
    staticStyle: {
      "height": "25px !important"
    }
  }, [_vm._v("Assign Name")])])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('thead', {
    staticStyle: {
      "position": "sticky",
      "top": "-1px",
      "z-index": "1"
    }
  }, [_c('tr', [_c('th', {
    staticStyle: {
      "height": "25px !important"
    }
  }, [_vm._v("S.No")]), _vm._v(" "), _c('th', {
    staticStyle: {
      "height": "25px !important"
    }
  }, [_vm._v("OBIS Code")]), _vm._v(" "), _c('th', {
    staticStyle: {
      "height": "25px !important"
    }
  }, [_vm._v("Default Name")]), _vm._v(" "), _c('th', {
    staticStyle: {
      "height": "25px !important"
    }
  }, [_vm._v("Assign Name")])])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('thead', {
    staticStyle: {
      "position": "sticky",
      "top": "-1px",
      "z-index": "1"
    }
  }, [_c('tr', [_c('th', {
    staticStyle: {
      "height": "25px !important"
    }
  }, [_vm._v("S.No")]), _vm._v(" "), _c('th', {
    staticStyle: {
      "height": "25px !important"
    }
  }, [_vm._v("OBIS Code")]), _vm._v(" "), _c('th', {
    staticStyle: {
      "height": "25px !important"
    }
  }, [_vm._v("Default Name")]), _vm._v(" "), _c('th', {
    staticStyle: {
      "height": "25px !important"
    }
  }, [_vm._v("Assign Name")])])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('thead', {
    staticStyle: {
      "position": "sticky",
      "top": "-1px",
      "z-index": "1"
    }
  }, [_c('tr', [_c('th', {
    staticStyle: {
      "height": "25px !important"
    }
  }, [_vm._v("S.No")]), _vm._v(" "), _c('th', {
    staticStyle: {
      "height": "25px !important"
    }
  }, [_vm._v("OBIS Code")]), _vm._v(" "), _c('th', {
    staticStyle: {
      "height": "25px !important"
    }
  }, [_vm._v("Default Name")]), _vm._v(" "), _c('th', {
    staticStyle: {
      "height": "25px !important"
    }
  }, [_vm._v("Assign Name")])])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('thead', {
    staticStyle: {
      "position": "sticky",
      "top": "-1px",
      "z-index": "1"
    }
  }, [_c('tr', [_c('th', {
    staticStyle: {
      "height": "25px !important"
    }
  }, [_vm._v("S.No")]), _vm._v(" "), _c('th', {
    staticStyle: {
      "height": "25px !important"
    }
  }, [_vm._v("OBIS Code")]), _vm._v(" "), _c('th', {
    staticStyle: {
      "height": "25px !important"
    }
  }, [_vm._v("Default Name")]), _vm._v(" "), _c('th', {
    staticStyle: {
      "height": "25px !important"
    }
  }, [_vm._v("Assign Name")])])])
}]}

/***/ }),
/* 131 */
/***/ (function(module, exports) {

module.exports={render:function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('div', [_c('ul', {
    staticClass: "sidebar-menu"
  }, [_c('li', {
    staticClass: "header",
    staticStyle: {
      "color": "white"
    }
  }, [_vm._v("MENU ")]), _vm._v(" "), _c('router-link', {
    staticClass: "pageLink",
    attrs: {
      "tag": "li",
      "to": "/dcu/deviceconfig"
    }
  }, [_c('a', [_c('i', {
    staticClass: "fa fa-cog text-white"
  }), _vm._v(" "), _c('span', {
    staticClass: "page"
  }, [_vm._v("Device Configuration")])])]), _vm._v(" "), _c('router-link', {
    staticClass: "pageLink",
    attrs: {
      "tag": "li",
      "to": "/dcu/upstreamconfig"
    }
  }, [_c('a', [_c('i', {
    staticClass: "fa fa-cogs text-white"
  }), _vm._v(" "), _c('span', {
    staticClass: "page"
  }, [_vm._v("Upstream Configuration")])])]), _vm._v(" "), _c('router-link', {
    staticClass: "pageLink",
    attrs: {
      "tag": "li",
      "to": "/dcu/paramsconfig"
    }
  }, [_c('a', [_c('i', {
    staticClass: "fa fa-star-half-o text-white"
  }), _vm._v(" "), _c('span', {
    staticClass: "page"
  }, [_vm._v("Parameter Configuration")])])]), _vm._v(" "), _c('router-link', {
    staticClass: "pageLink",
    attrs: {
      "tag": "li",
      "to": "/dcu/meterconfig"
    }
  }, [_c('a', [_c('i', {
    staticClass: "fa fa-sliders text-white"
  }), _vm._v(" "), _c('span', {
    staticClass: "page"
  }, [_vm._v("Meter Configuration")])])]), _vm._v(" "), _c('router-link', {
    staticClass: "pageLink",
    attrs: {
      "tag": "li",
      "to": "/dcu/status"
    }
  }, [_c('a', [_c('i', {
    staticClass: "fa fa-newspaper-o text-white"
  }), _vm._v(" "), _c('span', {
    staticClass: "page"
  }, [_vm._v("Status")])])]), _vm._v(" "), _c('router-link', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (false),
      expression: "false"
    }],
    staticClass: "pageLink",
    attrs: {
      "tag": "li",
      "to": "/dcu/viewdata"
    }
  }, [_c('a', [_c('i', {
    staticClass: "fa fa-eye text-white"
  }), _vm._v(" "), _c('span', {
    staticClass: "page"
  }, [_vm._v("View Data")])])]), _vm._v(" "), _c('router-link', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (false),
      expression: "false"
    }],
    staticClass: "pageLink",
    attrs: {
      "tag": "li",
      "to": "/dcu/ondemand"
    }
  }, [_c('a', [_c('i', {
    staticClass: "fa fa-comments-o text-white"
  }), _vm._v(" "), _c('span', {
    staticClass: "page"
  }, [_vm._v("On Demand")])])]), _vm._v(" "), _c('router-link', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (false),
      expression: "false"
    }],
    staticClass: "pageLink",
    attrs: {
      "tag": "li",
      "to": "/dcu/diagnostic"
    }
  }, [_c('a', [_c('i', {
    staticClass: "fa fa-search-plus text-white"
  }), _vm._v(" "), _c('span', {
    staticClass: "page"
  }, [_vm._v("Diagnostics")])])]), _vm._v(" "), _c('router-link', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (false),
      expression: "false"
    }],
    staticClass: "pageLink",
    attrs: {
      "tag": "li",
      "to": "/dcu/transferfirmware"
    }
  }, [_c('a', [_c('i', {
    staticClass: "fa fa-exchange text-white"
  }), _vm._v(" "), _c('span', {
    staticClass: "page"
  }, [_vm._v("Config / Firmware Transfer")])])]), _vm._v(" "), _c('hr', {
    staticStyle: {
      "margin-top": "5px",
      "margin-bottom": "5px"
    }
  }), _vm._v(" "), _c('router-link', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (false),
      expression: "false"
    }],
    staticClass: "pageLink",
    attrs: {
      "tag": "li",
      "to": "/dcu/servicehistory"
    }
  }, [_c('a', [_c('i', {
    staticClass: "fa fa-yelp text-white"
  }), _vm._v(" "), _c('span', {
    staticClass: "page"
  }, [_vm._v("Service")])])]), _vm._v(" "), _c('router-link', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (false),
      expression: "false"
    }],
    staticClass: "pageLink",
    attrs: {
      "tag": "li",
      "to": "/dcu/changepassword"
    }
  }, [_c('a', [_c('i', {
    staticClass: "fa fa-key text-white"
  }), _vm._v(" "), _c('span', {
    staticClass: "page"
  }, [_vm._v(" Change Password ")])])]), _vm._v(" "), _c('router-link', {
    staticClass: "pageLink",
    attrs: {
      "tag": "li",
      "to": "/dcu/saveandapply"
    }
  }, [_c('a', [_c('i', {
    staticClass: "fa fa-floppy-o text-white"
  }), _vm._v(" "), _c('span', {
    staticClass: "page"
  }, [_vm._v("Save & Apply")]), _vm._v(" "), _c('small', {
    staticClass: "label pull-right bg-green"
  }, [_c('i', {
    staticClass: "fa fa-check"
  })])])]), _vm._v(" "), _c('li', {
    staticClass: "pageLink",
    staticStyle: {
      "cursor": "pointer"
    },
    attrs: {
      "id": "sidebarresetunitBTN"
    },
    on: {
      "click": _vm.restartunitFunction
    }
  }, [_vm._m(0)]), _vm._v(" "), _c('router-link', {
    staticClass: "pageLink",
    attrs: {
      "tag": "li",
      "to": "/"
    }
  }, [_c('a', [_c('i', {
    staticClass: "fa fa-sign-out text-white"
  }), _vm._v(" "), _c('span', {
    staticClass: "page"
  }, [_vm._v(" Logout ")])])])], 1), _vm._v(" "), _c('BlockUI', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (_vm.blockdevice),
      expression: "blockdevice"
    }],
    attrs: {
      "message": _vm.msg,
      "html": _vm.html
    }
  }, [_c('div', {
    staticClass: "checkbox-wrapper"
  }, [_c('i', {
    staticClass: "fa fa-cogs fa-spin fa-3x fa-fw",
    staticStyle: {
      "color": "#1a495e"
    }
  }), _c('p'), _vm._v(" "), _c('p', {
    staticStyle: {
      "color": "#1a495e"
    }
  }, [_vm._v("Please wait while the system saves the configuration and resets, you will be redirected after " + _vm._s(_vm.time) + " seconds. ")])])])], 1)
},staticRenderFns: [function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('a', [_c('i', {
    staticClass: "fa fa-refresh text-white"
  }), _vm._v(" "), _c('span', {
    staticClass: "page"
  }, [_vm._v("Restart Unit")]), _vm._v(" "), _c('small', {
    staticClass: "label pull-right bg-blue"
  }, [_vm._v("R")])])
}]}

/***/ }),
/* 132 */
/***/ (function(module, exports) {

module.exports={render:function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('aside', {
    staticClass: "main-sidebar"
  }, [_c('section', {
    staticClass: "sidebar"
  }, [_vm._m(0), _vm._v(" "), _c('sidebar-menu')], 1)])
},staticRenderFns: [function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('div', {
    staticClass: "user-panel"
  }, [_c('div', {
    staticClass: "pull-left image"
  }, [_c('img', {
    attrs: {
      "src": "/static/img/images/dculogo2.png"
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "pull-left info"
  }, [_c('div', [_c('h5', {
    staticClass: "white",
    staticStyle: {
      "margin-top": "5px",
      "margin-bottom": "0px",
      "font-weight": "bold",
      "font-size": "20px"
    }
  }, [_vm._v("DCU")])])])])
}]}

/***/ }),
/* 133 */
/***/ (function(module, exports) {

module.exports={render:function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('header', {
    staticClass: "main-header"
  }, [_vm._m(0), _vm._v(" "), _c('nav', {
    staticClass: "navbar navbar-static-top",
    attrs: {
      "role": "navigation"
    }
  }, [_vm._m(1), _vm._v(" "), _c('div', {
    staticClass: "navbar-custom-menu"
  }, [_c('ul', {
    staticClass: "nav navbar-nav"
  }, [_c('notifications-menu'), _vm._v(" "), _c('user-menu', {
    attrs: {
      "user": _vm.user
    }
  })], 1)])])])
},staticRenderFns: [function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('span', {
    staticClass: "logo-mini"
  }, [_c('img', {
    staticClass: "img-responsive center-block logo",
    attrs: {
      "src": "/static/img/images/cmslogo_icon.png",
      "alt": "Logo"
    }
  })])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('a', {
    staticClass: "sidebar-toggle",
    attrs: {
      "href": "javascript:;",
      "data-toggle": "offcanvas",
      "role": "button"
    }
  }, [_c('span', {
    staticClass: "sr-only"
  }, [_vm._v("Toggle navigation")])])
}]}

/***/ }),
/* 134 */
/***/ (function(module, exports) {

module.exports={render:function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('section', {
    staticClass: "content",
    attrs: {
      "id": "deviceStatuspane"
    }
  }, [_c('vue-element-loading', {
    attrs: {
      "active": _vm.isLoading,
      "spinner": "spinner",
      "color": "#000",
      "is-full-screen": true
    }
  }), _vm._v(" "), (_vm.instaLLJSon != '') ? _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-12"
  }, [_c('ul', {
    staticClass: "timeline"
  }, [_c('li', [_c('i', {
    staticClass: "fa fa-newspaper-o bg-yellow"
  }), _vm._v(" "), _c('div', {
    staticClass: "timeline-item"
  }, [_c('h3', {
    staticClass: "timeline-header"
  }, [_vm._v("Device Data")]), _vm._v(" "), _c('div', {
    staticClass: "timeline-body"
  }, [_c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-12"
  }, [_vm._m(0), _vm._v(" "), _c('div', {
    staticClass: "tab-content"
  }, [_c('div', {
    staticClass: "tab-pane active",
    attrs: {
      "role": "tabpanel",
      "aria-labelledby": "devicedataTabPANE1",
      "id": "devicedataTabPANE1"
    }
  }, [_c('p'), _vm._v(" "), _c('h4', {
    staticClass: "timeline-header",
    staticStyle: {
      "text-decoration": "underline"
    }
  }, [_vm._v("\n                        Status:\n                      ")]), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-md-12"
  }, [
    [_c('div', {
      staticClass: "table-responsive",
      staticStyle: {
        "border": "1px solid lightgray"
      },
      style: ({
        height: _vm.deviceStatustableheight,
      }),
      attrs: {
        "id": "meterStatusTablePANE"
      }
    }, [_c('table', {
      staticClass: "table table-bordered table-responsive-stack",
      attrs: {
        "id": "meterStatusTable"
      }
    }, [_vm._m(1), _vm._v(" "), (_vm.instaLLJSon.DATA.NUM_METERS != '0') ? _c('tbody', _vm._l((_vm.instaLLJSon
      .DATA.INST_PARAM), function(inputItems, index) {
      return _c('tr', {
        key: index
      }, [_c('td', [_vm._v(_vm._s(index + 1))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(index + 1))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(inputItems.MET_LOC))]), _vm._v(" "), _c('td', [_vm._v("\n                                      " + _vm._s(inputItems.MET_SERNUM.trim()) + "\n                                    ")]), _vm._v(" "), (inputItems.COMM_STATUS == '1') ? _c('td', [_c('img', {
        attrs: {
          "src": "/static/img/images/comm.png",
          "width": "12"
        }
      }), _vm._v("      \n                                      Communicating\n                                    ")]) : (
        inputItems.COMM_STATUS == '0'
      ) ? _c('td', [_c('img', {
        attrs: {
          "src": "/static/img/images/notcomm.png",
          "width": "12"
        }
      }), _vm._v("\n                                      Not Communicating\n                                    ")]) : _c('td', [_c('img', {
        attrs: {
          "src": "/static/img/images/notconfig.png",
          "width": "12"
        }
      }), _vm._v("\n                                              Not Configured\n                                    ")]), _vm._v(" "), _c('td', [_vm._v("\n                                     " + _vm._s(inputItems.UPDATE_TIME) + "\n                                    ")]), _vm._v(" "), _c('td', {
        staticStyle: {
          "cursor": "pointer"
        },
        on: {
          "click": function($event) {
            return _vm.getmeterStatus(index)
          }
        }
      }, [_c('i', {
        staticClass: "fa fa-eye"
      })])])
    }), 0) : _vm._e()]), _vm._v(" "), (_vm.instaLLJSon.DATA.NUM_METERS == '0') ? _c('div', {
      staticClass: "text-center text-block"
    }, [_c('span', [_vm._v("No Records Found")])]) : _vm._e()])]
  ], 2)])]), _vm._v(" "), _c('div', {
    staticClass: "tab-pane",
    attrs: {
      "role": "tabpanel",
      "aria-labelledby": "devicedataTabPANE2",
      "id": "devicedataTabPANE2"
    }
  }, [_c('p'), _vm._v(" "), _c('h4', {
    staticClass: "timeline-header",
    staticStyle: {
      "text-decoration": "underline"
    }
  }, [_vm._v("\n                        Data:\n                      ")]), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-md-12"
  }, [
    [_c('div', {
      staticClass: "table-responsive",
      staticStyle: {
        "border": "1px solid lightgray",
        "overflow-x": "auto"
      },
      style: ({
        height: _vm.deviceStatustableheight,
      }),
      attrs: {
        "id": "meterStatusTablePANE"
      }
    }, [_c('table', {
      staticClass: "table table-bordered table-responsive-stack",
      attrs: {
        "id": "meterStatusTable"
      }
    }, [_c('thead', {
      staticStyle: {
        "position": "sticky",
        "top": "-1px",
        "z-index": "1"
      }
    }, [_c('tr', [_c('th', [_vm._v("S.No")]), _vm._v(" "), _c('th', {
      staticStyle: {
        "min-width": "120px"
      }
    }, [_vm._v("Meter Id")]), _vm._v(" "), _c('th', {
      staticStyle: {
        "min-width": "220px"
      }
    }, [_vm._v("Location")]), _vm._v(" "), _c('th', {
      staticStyle: {
        "min-width": "100px"
      }
    }, [_vm._v("\n                                      Serial Number\n                                    ")]), _vm._v(" "), _c('th', {
      staticStyle: {
        "min-width": "150px"
      }
    }, [_vm._v("\n                                      Comm Status\n                                    ")]), _vm._v(" "), _c('th', {
      staticStyle: {
        "min-width": "120px"
      }
    }, [_vm._v("\n                                      Last Update Time\n                                    ")]), _vm._v(" "), _vm._l((_vm.instaLLJSon.DATA
      .INST_PARAM[0].PARAMS), function(paramterdetailItem, paramterindex) {
      return _c('th', {
        key: paramterindex,
        staticStyle: {
          "min-width": "150px"
        }
      }, [_vm._v("\n                                      " + _vm._s(paramterdetailItem.PN) + "\n                                    ")])
    })], 2)]), _vm._v(" "), (_vm.instaLLJSon.DATA.NUM_METERS != '0') ? _c('tbody', _vm._l((_vm.instaLLJSon
      .DATA.INST_PARAM), function(inputItems, index) {
      return _c('tr', {
        key: index
      }, [_c('td', [_vm._v(_vm._s(index + 1))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(index + 1))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(inputItems.MET_LOC))]), _vm._v(" "), _c('td', [_vm._v("\n                                      " + _vm._s(inputItems.MET_SERNUM.trim()) + "\n                                    ")]), _vm._v(" "), (inputItems.COMM_STATUS == '1') ? _c('td', [_c('img', {
        attrs: {
          "src": "/static/img/images/comm.png",
          "width": "12"
        }
      }), _vm._v("      \n                                      Communicating\n                                    ")]) : (
        inputItems.COMM_STATUS == '0'
      ) ? _c('td', [_c('img', {
        attrs: {
          "src": "/static/img/images/notcomm.png",
          "width": "12"
        }
      }), _vm._v("\n                                      Not Communicating\n                                    ")]) : _c('td', [_c('img', {
        attrs: {
          "src": "/static/img/images/notconfig.png",
          "width": "12"
        }
      }), _vm._v("\n                                              Not Configured\n                                    ")]), _vm._v(" "), _c('td', [_vm._v("\n                                      " + _vm._s(inputItems.UPDATE_TIME) + "\n                                    ")]), _vm._v(" "), _vm._l((inputItems.PARAMS), function(locaItem, locIndex) {
        return _c('td', {
          key: locIndex
        }, [_vm._v("\n                                      " + _vm._s(locaItem.PV) + "\n                                    ")])
      })], 2)
    }), 0) : _vm._e()]), _vm._v(" "), (_vm.instaLLJSon.DATA.NUM_METERS == '0') ? _c('div', {
      staticClass: "text-center text-block"
    }, [_c('span', [_vm._v("No Records Found")])]) : _vm._e()])]
  ], 2)])])])])])])])])])])]) : _vm._e(), _vm._v(" "), _c('modal', {
    staticStyle: {
      "z-index": "1055"
    },
    attrs: {
      "name": "meterstatuspopup",
      "transition": "nice-modal-fade",
      "classes": "demo-modal-class",
      "min-width": 500,
      "min-height": 200,
      "pivot-y": 0.5,
      "adaptive": true,
      "draggable": true,
      "scrollable": true,
      "reset": true,
      "width": "65%",
      "height": "auto",
      "clickToClose": false
    },
    on: {
      "before-open": _vm.beforeOpen,
      "opened": _vm.meterstatuspopupopened,
      "closed": _vm.meterstatuspopupclosed,
      "before-close": _vm.beforeClose
    }
  }, [_c('div', {
    staticClass: "size-modal-content"
  }, [_c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "modal-header"
  }, [_c('div', {
    staticClass: "col-lg-6"
  }, [_c('h4', {
    staticClass: "heading",
    staticStyle: {
      "color": "rgb(0, 115, 183)"
    }
  }, [_vm._v("\n              Meter Status Details\n            ")])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-6 text-right",
    staticStyle: {
      "margin-top": "-10px"
    }
  }, [_c('button', {
    staticClass: "btn btn-default",
    staticStyle: {
      "background": "transparent",
      "border": "1px solid transparent"
    },
    attrs: {
      "id": "meterpopupcloseBTN",
      "type": "button"
    },
    on: {
      "click": _vm.meterstatuspopupclosed
    }
  }, [_c('span', {
    staticClass: "white-text",
    attrs: {
      "aria-hidden": "true"
    }
  }, [_vm._v("×")])])])])]), _vm._v(" "), _c('div', {
    staticClass: "modal-body",
    staticStyle: {
      "background-color": "white"
    }
  }, [_c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-3"
  }, [_c('b', [_vm._v("Meter Location")]), _vm._v(" : " + _vm._s(_vm.getmeterStatuspopupLocation) + "\n          ")]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-3"
  }, [_c('b', [_vm._v("Meter Serial Number")]), _vm._v(" : " + _vm._s(_vm.getmeterStatuspopupSerialNum) + "\n          ")]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-3"
  }, [_c('b', [_vm._v("Meter Status")]), _vm._v(" : " + _vm._s(_vm.getmeterStatuspopupCommStatus) + "\n          ")]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-3"
  }, [_c('b', [_vm._v("Update Time")]), _vm._v(" : " + _vm._s(_vm.getmeterStatuspopupUpdateTime) + "\n          ")])]), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-12"
  }, [_c('div', {
    staticClass: "table-responsive"
  }, [_vm._l((_vm.countlength), function(tableRow, tableIndex) {
    return _c('table', {
      key: tableIndex,
      staticClass: "table",
      attrs: {
        "id": "metStatusTableID"
      }
    }, [_c('tr', [_c('th', {
      staticStyle: {
        "width": "150px"
      }
    }, [_vm._v("parameter Name")]), _vm._v(" "), _vm._l((_vm.getmeterStatusArray), function(row, index) {
      return _c('span', {
        key: index
      }, [(
        index >= tableIndex * _vm.divLength &&
        index < tableIndex * _vm.divLength + _vm.divLength
      ) ? _c('td', {
        staticStyle: {
          "width": "150px",
          "height": "50px",
          "vertical-align": "middle"
        }
      }, [_c('b', [_vm._v(_vm._s(row.PN))])]) : _vm._e()])
    })], 2), _vm._v(" "), _c('tr', [_c('th', {
      staticStyle: {
        "width": "150px"
      }
    }, [_vm._v("Value")]), _vm._v(" "), _vm._l((_vm.getmeterStatusArray), function(row, index) {
      return _c('span', {
        key: index
      }, [(
        index >= tableIndex * _vm.divLength &&
        index < tableIndex * _vm.divLength + _vm.divLength
      ) ? _c('span', [_c('td', {
        staticStyle: {
          "width": "150px",
          "height": "50px",
          "vertical-align": "middle"
        }
      }, [_vm._v("\n                          " + _vm._s(row.PV) + "\n                        ")])]) : _vm._e()])
    })], 2)])
  })], 2)])])]), _vm._v(" "), _c('div', {
    staticClass: "modal-footer flex-center",
    staticStyle: {
      "background-color": "white",
      "padding": "10px"
    }
  }, [_c('a', {
    staticClass: "btn btn-default waves-effect btnPadding",
    attrs: {
      "id": "clseBTN",
      "type": "button"
    },
    on: {
      "click": _vm.meterstatuspopupclosed
    }
  }, [_vm._v("Cancel")])])])])], 1)
},staticRenderFns: [function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('div', {
    staticClass: "tab",
    attrs: {
      "role": "tabpanel"
    }
  }, [_c('ul', {
    staticClass: "nav nav-tabs",
    attrs: {
      "role": "tablist"
    }
  }, [_c('li', {
    staticClass: "active",
    attrs: {
      "role": "presentation",
      "id": "devicedataTab1"
    }
  }, [_c('a', {
    staticStyle: {
      "text-transform": "uppercase"
    },
    attrs: {
      "id": "devicedataTabbutton1",
      "href": "#devicedataTabPANE1",
      "aria-controls": "home",
      "role": "tab",
      "data-toggle": "tab"
    }
  }, [_c('i', {
    staticClass: "fa fa-desktop iconbg",
    attrs: {
      "aria-hidden": "true"
    }
  }), _vm._v("\n                             Meter Status\n                        ")])]), _vm._v(" "), _c('li', {
    attrs: {
      "role": "presentation",
      "id": "devicedataTab2"
    }
  }, [_c('a', {
    staticStyle: {
      "text-transform": "uppercase"
    },
    attrs: {
      "id": "devicedataTabbutton2",
      "href": "#devicedataTabPANE2",
      "aria-controls": "home",
      "role": "tab",
      "data-toggle": "tab"
    }
  }, [_c('i', {
    staticClass: "fa fa-desktop iconbg",
    attrs: {
      "aria-hidden": "true"
    }
  }), _vm._v("\n                             Meter Data\n                        ")])])])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('thead', {
    staticStyle: {
      "position": "sticky",
      "top": "-1px",
      "z-index": "1"
    }
  }, [_c('tr', [_c('th', [_vm._v("S.No")]), _vm._v(" "), _c('th', [_vm._v("Meter Id")]), _vm._v(" "), _c('th', [_vm._v("Location")]), _vm._v(" "), _c('th', [_vm._v("Serial Number")]), _vm._v(" "), _c('th', [_vm._v("Comm Status")]), _vm._v(" "), _c('th', [_vm._v("Last Update Time")]), _vm._v(" "), _c('th', [_vm._v("View")])])])
}]}

/***/ }),
/* 135 */
/***/ (function(module, exports) {

module.exports={render:function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('section', {
    staticClass: "content",
    attrs: {
      "id": "viewDATAPage"
    }
  }, [_c('vue-element-loading', {
    attrs: {
      "active": _vm.isLoading,
      "spinner": "spinner",
      "color": "#000",
      "is-full-screen": true
    }
  }), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-12"
  }, [_c('ul', {
    staticClass: "timeline"
  }, [_c('li', [_c('i', {
    staticClass: "fa fa-key bg-yellow"
  }), _vm._v(" "), _c('div', {
    staticClass: "timeline-item"
  }, [_c('div', {
    staticClass: "timeline-body"
  }, [_c('div', {
    staticClass: "row"
  }, [_vm._m(0), _vm._v(" "), _c('div', {
    staticClass: "col-lg-3"
  }, [_c('select', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.viewdataMeterLocTXT),
      expression: "viewdataMeterLocTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "name": "meterlocation",
      "id": "viewdataMeterLocTXT"
    },
    on: {
      "change": function($event) {
        var $$selectedVal = Array.prototype.filter.call($event.target.options, function(o) {
          return o.selected
        }).map(function(o) {
          var val = "_value" in o ? o._value : o.value;
          return val
        });
        _vm.viewdataMeterLocTXT = $event.target.multiple ? $$selectedVal : $$selectedVal[0]
      }
    }
  }, [_c('option', {
    attrs: {
      "value": "Choose Meter Location",
      "selected": ""
    }
  }, [_vm._v("Choose Meter Location")])])])]), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_vm._m(1), _vm._v(" "), _c('div', {
    staticClass: "col-lg-3"
  }, [_c('select', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.viewdataMeterDataTypeTXT),
      expression: "viewdataMeterDataTypeTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "name": "meterdatatype",
      "id": "viewdataMeterDataTypeTXT"
    },
    on: {
      "change": function($event) {
        var $$selectedVal = Array.prototype.filter.call($event.target.options, function(o) {
          return o.selected
        }).map(function(o) {
          var val = "_value" in o ? o._value : o.value;
          return val
        });
        _vm.viewdataMeterDataTypeTXT = $event.target.multiple ? $$selectedVal : $$selectedVal[0]
      }
    }
  }, [_c('option', {
    attrs: {
      "value": "Choose Data Type",
      "selected": ""
    }
  }, [_vm._v("Choose Data Type")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "GET Load Survey Data"
    }
  }, [_vm._v("GET Load Survey Data")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "GET Daily Profile Data"
    }
  }, [_vm._v("GET Daily Profile Data")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "GET Billing Data"
    }
  }, [_vm._v("GET Billing Data")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "GET Event Data"
    }
  }, [_vm._v("GET Event Data")])])])]), _vm._v(" "), _c('p'), _vm._v(" "), _vm._m(2), _vm._v(" "), _c('p'), _vm._v(" "), _vm._m(3), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-12"
  }, [
    [_c('div', {
      staticClass: "table-responsive",
      staticStyle: {
        "border": "1px solid lightgray"
      },
      style: ({
        height: _vm.viewDataTableheight
      }),
      attrs: {
        "id": "viewDataTablePane"
      }
    }, [_c('table', {
      staticClass: "table table-bordered table-responsive-stack",
      attrs: {
        "id": "viewDataTableID"
      }
    }, [_vm._m(4), _vm._v(" "), (_vm.viewDataconfigJson != '') ? _c('tbody', _vm._l((_vm.viewDataconfigJson.details), function(inputItems, index) {
      return _c('tr', {
        key: index
      }, [_c('td', [_vm._v(_vm._s(index + 1))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(inputItems.date))]), _vm._v(" "), _c('td', [_c('a', {
        staticClass: "hyperlink",
        on: {
          "click": function($event) {
            return _vm.viewDATA()
          }
        }
      }, [_vm._v("View")])]), _vm._v(" "), _c('td', [_c('a', {
        staticClass: "hyperlink",
        on: {
          "click": function($event) {
            return _vm.downloadDATA()
          }
        }
      }, [_vm._v("Download")])])])
    }), 0) : _vm._e()]), _vm._v(" "), (_vm.viewDataconfigJson == '') ? _c('div', {
      staticClass: "text-center text-block"
    }, [_c('span', [_vm._v("No Records Found")])]) : _vm._e()])]
  ], 2)])])])])])])])], 1)
},staticRenderFns: [function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Choose Meter Data Location :")])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Choose Data Type :")])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-2"
  }), _vm._v(" "), _c('div', {
    staticClass: "col-lg-4"
  }, [_c('button', {
    staticClass: "btn btn-sm btn-default",
    attrs: {
      "id": "viewdataApplyBTN",
      "type": "button"
    }
  }, [_vm._v("\n                            Apply\n                      ")])])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-2"
  }, [_c('h5', [_c('b', [_vm._v("Details :")])])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-4"
  })])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('thead', {
    staticStyle: {
      "position": "sticky",
      "top": "-1px",
      "z-index": "1"
    }
  }, [_c('tr', [_c('th', [_vm._v("S.No")]), _vm._v(" "), _c('th', [_vm._v("Date")]), _vm._v(" "), _c('th', [_vm._v("View")]), _vm._v(" "), _c('th', [_vm._v("Download")])])])
}]}

/***/ }),
/* 136 */
/***/ (function(module, exports) {

module.exports={render:function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('li', {
    staticClass: "dropdown notifications-menu"
  }, [_vm._m(0), _vm._v(" "), _c('ul', {
    staticClass: "dropdown-menu"
  }, [_c('li', {
    staticClass: "header"
  }, [_c('div', {
    staticClass: "row no-margin"
  }, [_c('span', {
    staticClass: "col-xs-12 col-md-6 tab-link",
    class: {
      active: _vm.tab === 'new'
    },
    on: {
      "click": function($event) {
        return _vm.switchTab($event, 'new')
      }
    }
  }, [_c('a', {
    attrs: {
      "href": "javascript:;"
    }
  }, [_vm._v("Version Details")])]), _vm._v(" "), _c('span', {
    staticClass: "col-xs-12 col-md-6 tab-link",
    class: {
      active: _vm.tab === 'old'
    },
    on: {
      "click": function($event) {
        return _vm.switchTab($event, 'old')
      }
    }
  }, [_c('a', {
    attrs: {
      "href": "javascript:;"
    }
  })])])]), _vm._v(" "), _c('li', [(_vm.tab === 'new') ? _c('ul', {
    staticClass: "menu"
  }, [_vm._m(1), _vm._v(" "), _c('p'), _vm._v(" "), (!_vm.newNotifications.length) ? _c('li', [_c('span', {
    staticClass: "center-block text-center"
  }, [_vm._v("There are no version available")])]) : _vm._e()]) : _vm._e(), _vm._v(" "), (_vm.tab === 'old') ? _c('ul', {
    staticClass: "menu"
  }) : _vm._e()])])])
},staticRenderFns: [function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('a', {
    staticClass: "dropdown-toggle",
    attrs: {
      "href": "javascript:;",
      "data-toggle": "dropdown"
    }
  }, [_c('i', {
    staticClass: "fa fa-info-circle",
    staticStyle: {
      "font-size": "20px"
    }
  })])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-12"
  }, [_c('div', {
    staticClass: "col-lg-4"
  }, [_vm._v("SR No")]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-1"
  }, [_vm._v(":")]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-7"
  }, [_c('b', [_vm._v("DCU-DEFAULT-SERNO")])])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-12"
  }, [_c('div', {
    staticClass: "col-lg-4"
  }, [_vm._v("Model No")]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-1"
  }, [_vm._v(":")]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-7"
  }, [_c('b', [_vm._v("CS-MDAS-DCU-160X-1001")])])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-12"
  }, [_c('div', {
    staticClass: "col-lg-4"
  }, [_vm._v("FW Ver")]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-1"
  }, [_vm._v(":")]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-7"
  }, [_c('b', [_vm._v("V3.0 27July2020")])])])])
}]}

/***/ }),
/* 137 */
/***/ (function(module, exports) {

module.exports={render:function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('section', {
    staticClass: "content",
    attrs: {
      "id": "onDemandPage"
    }
  }, [_c('vue-element-loading', {
    attrs: {
      "active": _vm.isLoading,
      "spinner": "spinner",
      "color": "#000",
      "is-full-screen": true
    }
  }), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-12"
  }, [_c('ul', {
    staticClass: "timeline"
  }, [_c('li', [_c('i', {
    staticClass: "fa fa-comments-o bg-yellow"
  }), _vm._v(" "), _c('div', {
    staticClass: "timeline-item"
  }, [_c('div', {
    staticClass: "timeline-body"
  }, [_c('div', {
    staticClass: "row"
  }, [_vm._m(0), _vm._v(" "), _c('div', {
    staticClass: "col-lg-3"
  }, [_c('select', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.onDemandSerialNoTXT),
      expression: "onDemandSerialNoTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "name": "onDemandSerialNo",
      "id": "onDemandSerialNoTXT"
    },
    on: {
      "change": function($event) {
        var $$selectedVal = Array.prototype.filter.call($event.target.options, function(o) {
          return o.selected
        }).map(function(o) {
          var val = "_value" in o ? o._value : o.value;
          return val
        });
        _vm.onDemandSerialNoTXT = $event.target.multiple ? $$selectedVal : $$selectedVal[0]
      }
    }
  }, [_c('option', {
    attrs: {
      "value": "Meter Serial Number",
      "selected": "",
      "disabled": ""
    }
  }, [_vm._v("Meter Serial Number")])])])]), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_vm._m(1), _vm._v(" "), _c('div', {
    staticClass: "col-lg-3"
  }, [_c('select', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.onDemandCommandTXT),
      expression: "onDemandCommandTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "name": "onDemandCommand",
      "id": "onDemandCommandTXT"
    },
    on: {
      "change": function($event) {
        var $$selectedVal = Array.prototype.filter.call($event.target.options, function(o) {
          return o.selected
        }).map(function(o) {
          var val = "_value" in o ? o._value : o.value;
          return val
        });
        _vm.onDemandCommandTXT = $event.target.multiple ? $$selectedVal : $$selectedVal[0]
      }
    }
  }, [_c('option', {
    attrs: {
      "value": "Choose Command",
      "selected": "",
      "disabled": ""
    }
  }, [_vm._v("Choose Command")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "Get Instantaneous Data"
    }
  }, [_vm._v("Get Instantaneous Data")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "Get Load Survey Data (Today)"
    }
  }, [_vm._v("Get Load Survey Data (Today)")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "Get Load Survey Data (For n days)"
    }
  }, [_vm._v("Get Load Survey Data (For n days)")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "Get Billing Data"
    }
  }, [_vm._v("Get Billing Data")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "Get Event Data"
    }
  }, [_vm._v("Get Event Data")])])])]), _vm._v(" "), _c('p'), _vm._v(" "), _vm._m(2), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (false),
      expression: "false"
    }],
    staticClass: "row"
  }, [_vm._m(3), _vm._v(" "), _c('div', {
    staticClass: "col-lg-4"
  })]), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (false),
      expression: "false"
    }],
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-12"
  }, [
    [_c('div', {
      staticClass: "table-responsive",
      staticStyle: {
        "border": "1px solid lightgray"
      },
      style: ({
        height: _vm.onDemandTableheight
      }),
      attrs: {
        "id": "onDemandTablePane"
      }
    }, [_c('table', {
      staticClass: "table table-bordered table-responsive-stack",
      attrs: {
        "id": "onDemandTableID"
      }
    }, [_vm._m(4), _vm._v(" "), (_vm.ondemandconfigJson != '') ? _c('tbody', _vm._l((_vm.ondemandconfigJson.details), function(inputItems, index) {
      return _c('tr', {
        key: index
      }, [_c('td', [_vm._v(_vm._s(index + 1))]), _vm._v(" "), _c('td', [_vm._v(_vm._s(inputItems.date))]), _vm._v(" "), _c('td', [_c('a', {
        staticClass: "hyperlink",
        on: {
          "click": function($event) {
            return _vm.viewDATA()
          }
        }
      }, [_vm._v("View")])]), _vm._v(" "), _c('td', [_c('a', {
        staticClass: "hyperlink",
        on: {
          "click": function($event) {
            return _vm.downloadDATA()
          }
        }
      }, [_vm._v("Download")])])])
    }), 0) : _vm._e()]), _vm._v(" "), (_vm.ondemandconfigJson == '') ? _c('div', {
      staticClass: "text-center text-block"
    }, [_c('span', [_vm._v("No Records Found")])]) : _vm._e()])]
  ], 2)])])])])])])])], 1)
},staticRenderFns: [function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Meter Serial Number :")])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Command :")])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-2"
  }), _vm._v(" "), _c('div', {
    staticClass: "col-lg-4"
  }, [_c('button', {
    staticClass: "btn btn-sm btn-default",
    attrs: {
      "id": "viewdataApplyBTN",
      "type": "button"
    }
  }, [_vm._v("\n                            Apply\n                      ")])])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('div', {
    staticClass: "col-lg-2"
  }, [_c('h5', [_c('b', [_vm._v("Details :")])])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('thead', {
    staticStyle: {
      "position": "sticky",
      "top": "-1px",
      "z-index": "1"
    }
  }, [_c('tr', [_c('th', [_vm._v("S.No")]), _vm._v(" "), _c('th', [_vm._v("Date")]), _vm._v(" "), _c('th', [_vm._v("View")]), _vm._v(" "), _c('th', [_vm._v("Download")])])])
}]}

/***/ }),
/* 138 */
/***/ (function(module, exports) {

module.exports={render:function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('section', {
    staticClass: "content",
    attrs: {
      "id": "meterconfigpane"
    }
  }, [_c('vue-element-loading', {
    attrs: {
      "active": _vm.isLoading,
      "spinner": "spinner",
      "color": "#000",
      "is-full-screen": true
    }
  }), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-12"
  }, [_c('ul', {
    staticClass: "timeline"
  }, [_c('li', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (_vm.meterCONFIGPageJSON.DATA.DLMSCfg.MeterType == 'Ethernet'),
      expression: "meterCONFIGPageJSON.DATA.DLMSCfg.MeterType == 'Ethernet'"
    }]
  }, [_c('i', {
    staticClass: "fa fa-sliders bg-yellow"
  }), _vm._v(" "), _c('div', {
    staticClass: "timeline-item"
  }, [_c('span', {
    staticClass: "time"
  }, [_vm._v(" ")]), _vm._v(" "), _c('h3', {
    staticClass: "timeline-header"
  }, [_vm._v("Configuration")]), _vm._v(" "), _c('div', {
    staticClass: "timeline-body"
  }, [_c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-12"
  }, [_vm._m(0), _vm._v(" "), _c('div', {
    staticClass: "col-lg-11"
  }, [_c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.instantaneousETHchekbox),
      expression: "instantaneousETHchekbox"
    }],
    attrs: {
      "type": "checkbox",
      "id": "instantaneousETHchekbox",
      "disabled": true
    },
    domProps: {
      "checked": Array.isArray(_vm.instantaneousETHchekbox) ? _vm._i(_vm.instantaneousETHchekbox, null) > -1 : (_vm.instantaneousETHchekbox)
    },
    on: {
      "change": function($event) {
        var $$a = _vm.instantaneousETHchekbox,
          $$el = $event.target,
          $$c = $$el.checked ? (true) : (false);
        if (Array.isArray($$a)) {
          var $$v = null,
            $$i = _vm._i($$a, $$v);
          if ($$el.checked) {
            $$i < 0 && (_vm.instantaneousETHchekbox = $$a.concat([$$v]))
          } else {
            $$i > -1 && (_vm.instantaneousETHchekbox = $$a.slice(0, $$i).concat($$a.slice($$i + 1)))
          }
        } else {
          _vm.instantaneousETHchekbox = $$c
        }
      }
    }
  }), _vm._v(" "), _c('label', {
    staticClass: "inputcheckTEXTLBLcss",
    attrs: {
      "for": "instantaneousETHchekbox"
    }
  }, [_vm._v("Instantaneous ")]), _vm._v("             \n                       "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.loadserveETHchekbox),
      expression: "loadserveETHchekbox"
    }],
    attrs: {
      "type": "checkbox",
      "id": "loadserveETHchekbox",
      "disabled": true
    },
    domProps: {
      "checked": Array.isArray(_vm.loadserveETHchekbox) ? _vm._i(_vm.loadserveETHchekbox, null) > -1 : (_vm.loadserveETHchekbox)
    },
    on: {
      "change": function($event) {
        var $$a = _vm.loadserveETHchekbox,
          $$el = $event.target,
          $$c = $$el.checked ? (true) : (false);
        if (Array.isArray($$a)) {
          var $$v = null,
            $$i = _vm._i($$a, $$v);
          if ($$el.checked) {
            $$i < 0 && (_vm.loadserveETHchekbox = $$a.concat([$$v]))
          } else {
            $$i > -1 && (_vm.loadserveETHchekbox = $$a.slice(0, $$i).concat($$a.slice($$i + 1)))
          }
        } else {
          _vm.loadserveETHchekbox = $$c
        }
      }
    }
  }), _vm._v(" "), _c('label', {
    staticClass: "inputcheckTEXTLBLcss",
    attrs: {
      "for": "loadserveETHchekbox"
    }
  }, [_vm._v("Load Survey ")]), _vm._v("             \n                        "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.eventdataETHchekbox),
      expression: "eventdataETHchekbox"
    }],
    attrs: {
      "type": "checkbox",
      "id": "eventdataETHchekbox",
      "disabled": true
    },
    domProps: {
      "checked": Array.isArray(_vm.eventdataETHchekbox) ? _vm._i(_vm.eventdataETHchekbox, null) > -1 : (_vm.eventdataETHchekbox)
    },
    on: {
      "change": function($event) {
        var $$a = _vm.eventdataETHchekbox,
          $$el = $event.target,
          $$c = $$el.checked ? (true) : (false);
        if (Array.isArray($$a)) {
          var $$v = null,
            $$i = _vm._i($$a, $$v);
          if ($$el.checked) {
            $$i < 0 && (_vm.eventdataETHchekbox = $$a.concat([$$v]))
          } else {
            $$i > -1 && (_vm.eventdataETHchekbox = $$a.slice(0, $$i).concat($$a.slice($$i + 1)))
          }
        } else {
          _vm.eventdataETHchekbox = $$c
        }
      }
    }
  }), _vm._v(" "), _c('label', {
    staticClass: "inputcheckTEXTLBLcss",
    attrs: {
      "for": "eventdataETHchekbox"
    }
  }, [_vm._v("Event Data ")]), _vm._v("             \n                        "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.midnightETHchekbox),
      expression: "midnightETHchekbox"
    }],
    attrs: {
      "type": "checkbox",
      "id": "midnightETHchekbox",
      "checked": "false"
    },
    domProps: {
      "checked": Array.isArray(_vm.midnightETHchekbox) ? _vm._i(_vm.midnightETHchekbox, null) > -1 : (_vm.midnightETHchekbox)
    },
    on: {
      "change": function($event) {
        var $$a = _vm.midnightETHchekbox,
          $$el = $event.target,
          $$c = $$el.checked ? (true) : (false);
        if (Array.isArray($$a)) {
          var $$v = null,
            $$i = _vm._i($$a, $$v);
          if ($$el.checked) {
            $$i < 0 && (_vm.midnightETHchekbox = $$a.concat([$$v]))
          } else {
            $$i > -1 && (_vm.midnightETHchekbox = $$a.slice(0, $$i).concat($$a.slice($$i + 1)))
          }
        } else {
          _vm.midnightETHchekbox = $$c
        }
      }
    }
  }), _vm._v(" "), _c('label', {
    staticClass: "inputcheckTEXTLBLcss",
    attrs: {
      "for": "midnightETHchekbox"
    }
  }, [_vm._v("Midnight ")]), _vm._v("      "), _c('i', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (_vm.midnightETHchekbox),
      expression: "midnightETHchekbox"
    }],
    staticClass: "fa fa-clock-o",
    attrs: {
      "aria-hidden": "true"
    }
  }), _vm._v(" "), _c('span', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (_vm.midnightETHchekbox),
      expression: "midnightETHchekbox"
    }],
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Poll Period ( in hours ) : ")]), _vm._v(" "), _c('select', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.midnightETHpollPeroidTXT),
      expression: "midnightETHpollPeroidTXT"
    }, {
      name: "show",
      rawName: "v-show",
      value: (_vm.midnightETHchekbox),
      expression: "midnightETHchekbox"
    }],
    staticClass: "inputTEXTcss",
    staticStyle: {
      "width": "100px"
    },
    on: {
      "change": function($event) {
        var $$selectedVal = Array.prototype.filter.call($event.target.options, function(o) {
          return o.selected
        }).map(function(o) {
          var val = "_value" in o ? o._value : o.value;
          return val
        });
        _vm.midnightETHpollPeroidTXT = $event.target.multiple ? $$selectedVal : $$selectedVal[0]
      }
    }
  }, [_c('option', {
    attrs: {
      "value": "1",
      "selected": ""
    }
  }, [_vm._v("1")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "2"
    }
  }, [_vm._v("2")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "4"
    }
  }, [_vm._v("4")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "6"
    }
  }, [_vm._v("6")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "12"
    }
  }, [_vm._v("12")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "24"
    }
  }, [_vm._v("24")])]), _vm._v("        \n                       "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.billingETHchekbox),
      expression: "billingETHchekbox"
    }],
    attrs: {
      "type": "checkbox",
      "id": "billingETHchekbox",
      "checked": "false"
    },
    domProps: {
      "checked": Array.isArray(_vm.billingETHchekbox) ? _vm._i(_vm.billingETHchekbox, null) > -1 : (_vm.billingETHchekbox)
    },
    on: {
      "change": function($event) {
        var $$a = _vm.billingETHchekbox,
          $$el = $event.target,
          $$c = $$el.checked ? (true) : (false);
        if (Array.isArray($$a)) {
          var $$v = null,
            $$i = _vm._i($$a, $$v);
          if ($$el.checked) {
            $$i < 0 && (_vm.billingETHchekbox = $$a.concat([$$v]))
          } else {
            $$i > -1 && (_vm.billingETHchekbox = $$a.slice(0, $$i).concat($$a.slice($$i + 1)))
          }
        } else {
          _vm.billingETHchekbox = $$c
        }
      }
    }
  }), _vm._v(" "), _c('label', {
    staticClass: "inputcheckTEXTLBLcss",
    attrs: {
      "for": "billingETHchekbox"
    }
  }, [_vm._v("Billing ")]), _vm._v("     "), _c('i', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (_vm.billingETHchekbox),
      expression: "billingETHchekbox"
    }],
    staticClass: "fa fa-clock-o",
    attrs: {
      "aria-hidden": "true"
    }
  }), _vm._v(" "), _c('span', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (_vm.billingETHchekbox),
      expression: "billingETHchekbox"
    }],
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Poll Period ( in hours ) : ")]), _vm._v(" "), _c('select', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.billingETHpollPeroidTXT),
      expression: "billingETHpollPeroidTXT"
    }, {
      name: "show",
      rawName: "v-show",
      value: (_vm.billingETHchekbox),
      expression: "billingETHchekbox"
    }],
    staticClass: "inputTEXTcss",
    staticStyle: {
      "width": "100px"
    },
    on: {
      "change": function($event) {
        var $$selectedVal = Array.prototype.filter.call($event.target.options, function(o) {
          return o.selected
        }).map(function(o) {
          var val = "_value" in o ? o._value : o.value;
          return val
        });
        _vm.billingETHpollPeroidTXT = $event.target.multiple ? $$selectedVal : $$selectedVal[0]
      }
    }
  }, [_c('option', {
    attrs: {
      "value": "1",
      "selected": ""
    }
  }, [_vm._v("1")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "2"
    }
  }, [_vm._v("2")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "4"
    }
  }, [_vm._v("4")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "6"
    }
  }, [_vm._v("6")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "12"
    }
  }, [_vm._v("12")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "24"
    }
  }, [_vm._v("24")])]), _vm._v("        \n                 ")]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-1 text-right"
  }, [_c('button', {
    staticClass: "btn btn-default",
    attrs: {
      "title": "Add Meter",
      "id": "addmeter_ETHBTN"
    },
    on: {
      "click": function($event) {
        return _vm.addETHmeterBTN()
      }
    }
  }, [_c('i', {
    staticClass: "fa fa-plus"
  }), _vm._v(" Add Meter")])]), _vm._v(" "), _c('p')])]), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-12"
  }, [
    [_c('div', {
      staticClass: "table-responsive",
      staticStyle: {
        "border": "1px solid lightgray"
      },
      style: ({
        height: _vm.tableheight
      }),
      attrs: {
        "id": "meterconfigethnetTablePane"
      }
    }, [_c('table', {
      staticClass: "table table-bordered table-responsive-stack",
      attrs: {
        "id": "meterconfigethnetTableID"
      }
    }, [_c('thead', {
      staticStyle: {
        "position": "sticky",
        "top": "-1px",
        "z-index": "1"
      }
    }, [_c('tr', [_c('th', [_vm._v("S.No")]), _vm._v(" "), _c('th', {
      directives: [{
        name: "show",
        rawName: "v-show",
        value: (false),
        expression: "false"
      }],
      staticStyle: {
        "width": "150px"
      }
    }, [_vm._v("Enable")]), _vm._v(" "), _c('th', [_vm._v("Meter IP")]), _vm._v(" "), _c('th', [_vm._v("Port")]), _vm._v(" "), _c('th', [_vm._v("Password")]), _vm._v(" "), _c('th', [_vm._v("Meter Location")]), _vm._v(" "), _c('th', [_vm._v("Timeout (in sec)")]), _vm._v(" "), _c('th', [_vm._v("Ret Count")]), _vm._v(" "), _c('th', [_vm._v("Delete")])])]), _vm._v(" "), (_vm.meterCONFIGPageJSON.DATA.DLMSEthMetCfg.NumMeters != '0') ? _c('tbody', _vm._l((_vm.meterCONFIGPageJSON.DATA.DLMSEthMetCfg.EthMeters), function(inputItems, index) {
      return _c('tr', {
        key: index
      }, [_c('td', [_vm._v(_vm._s(index + 1))]), _vm._v(" "), _c('td', {
        directives: [{
          name: "show",
          rawName: "v-show",
          value: (false),
          expression: "false"
        }],
        staticClass: "center-block text-center"
      }, [_c('input', {
        staticClass: "checkbox1",
        attrs: {
          "type": "checkbox",
          "id": 'ethnetcheckbox' + (index + 1)
        },
        domProps: {
          "checked": inputItems.Enable == '1' ? true : false
        },
        on: {
          "click": function($event) {
            return _vm.enableEthnetMeterdevice(index, inputItems)
          }
        }
      })]), _vm._v(" "), _c('td', [_c('input', {
        staticClass: "inputTEXTcss center-block text-center",
        attrs: {
          "type": "text",
          "id": 'ethnetipaddress' + (index + 1),
          "disabled": inputItems.Enable == '0' ? true : false
        },
        domProps: {
          "value": inputItems.Ip
        },
        on: {
          "change": function($event) {
            return _vm.saveMeterConfigPage()
          }
        }
      })]), _vm._v(" "), _c('td', [_c('input', {
        staticClass: "inputTEXTcss center-block text-center",
        attrs: {
          "type": "text",
          "id": 'ethnetport' + (index + 1),
          "disabled": inputItems.Enable == '0' ? true : false
        },
        domProps: {
          "value": inputItems.Port
        },
        on: {
          "change": function($event) {
            return _vm.saveMeterConfigPage()
          }
        }
      })]), _vm._v(" "), _c('td', [_c('input', {
        staticClass: "inputTEXTcss center-block text-center",
        attrs: {
          "type": "password",
          "id": 'ethnetPwd' + (index + 1),
          "disabled": inputItems.Enable == '0' ? true : false
        },
        domProps: {
          "value": inputItems.Pwd
        },
        on: {
          "change": function($event) {
            return _vm.saveMeterConfigPage()
          }
        }
      })]), _vm._v(" "), _c('td', [_c('input', {
        staticClass: "inputTEXTcss center-block text-center",
        attrs: {
          "type": "text",
          "id": 'ethnetLoc' + (index + 1),
          "disabled": inputItems.Enable == '0' ? true : false
        },
        domProps: {
          "value": inputItems.Loc
        },
        on: {
          "change": function($event) {
            return _vm.saveMeterConfigPage()
          }
        }
      })]), _vm._v(" "), _c('td', [_c('select', {
        staticClass: "inputTEXTcss center-block text-center",
        attrs: {
          "id": 'ethnetTO' + (index + 1),
          "disabled": inputItems.Enable == '0' ? true : false
        },
        domProps: {
          "value": inputItems.TO
        },
        on: {
          "change": function($event) {
            return _vm.saveMeterConfigPage()
          }
        }
      }, [_c('option', {
        attrs: {
          "value": "Choose Timeout",
          "selected": "",
          "disabled": ""
        }
      }, [_vm._v("Choose Timeout")]), _vm._v(" "), _c('option', {
        attrs: {
          "value": "1"
        }
      }, [_vm._v("1")]), _vm._v(" "), _c('option', {
        attrs: {
          "value": "2"
        }
      }, [_vm._v("2")]), _vm._v(" "), _c('option', {
        attrs: {
          "value": "3"
        }
      }, [_vm._v("3")]), _vm._v(" "), _c('option', {
        attrs: {
          "value": "4"
        }
      }, [_vm._v("4")]), _vm._v(" "), _c('option', {
        attrs: {
          "value": "5"
        }
      }, [_vm._v("5")]), _vm._v(" "), _c('option', {
        attrs: {
          "value": "6"
        }
      }, [_vm._v("6")]), _vm._v(" "), _c('option', {
        attrs: {
          "value": "7"
        }
      }, [_vm._v("7")]), _vm._v(" "), _c('option', {
        attrs: {
          "value": "8"
        }
      }, [_vm._v("8")]), _vm._v(" "), _c('option', {
        attrs: {
          "value": "9"
        }
      }, [_vm._v("9")]), _vm._v(" "), _c('option', {
        attrs: {
          "value": "10"
        }
      }, [_vm._v("10")])])]), _vm._v(" "), _c('td', [_c('select', {
        staticClass: "inputTEXTcss center-block text-center",
        attrs: {
          "id": 'ethnetRetCnt' + (index + 1),
          "disabled": inputItems.Enable == '0' ? true : false
        },
        domProps: {
          "value": inputItems.RetCnt
        },
        on: {
          "change": function($event) {
            return _vm.saveMeterConfigPage()
          }
        }
      }, [_c('option', {
        attrs: {
          "value": "Choose Count",
          "selected": "",
          "disabled": ""
        }
      }, [_vm._v("Choose Count")]), _vm._v(" "), _c('option', {
        attrs: {
          "value": "1"
        }
      }, [_vm._v("1")]), _vm._v(" "), _c('option', {
        attrs: {
          "value": "2"
        }
      }, [_vm._v("2")]), _vm._v(" "), _c('option', {
        attrs: {
          "value": "3"
        }
      }, [_vm._v("3")]), _vm._v(" "), _c('option', {
        attrs: {
          "value": "4"
        }
      }, [_vm._v("4")]), _vm._v(" "), _c('option', {
        attrs: {
          "value": "5"
        }
      }, [_vm._v("5")]), _vm._v(" "), _c('option', {
        attrs: {
          "value": "6"
        }
      }, [_vm._v("6")]), _vm._v(" "), _c('option', {
        attrs: {
          "value": "7"
        }
      }, [_vm._v("7")]), _vm._v(" "), _c('option', {
        attrs: {
          "value": "8"
        }
      }, [_vm._v("8")]), _vm._v(" "), _c('option', {
        attrs: {
          "value": "9"
        }
      }, [_vm._v("9")]), _vm._v(" "), _c('option', {
        attrs: {
          "value": "10"
        }
      }, [_vm._v("10")])])]), _vm._v(" "), _c('td', [_c('img', {
        attrs: {
          "id": 'ethnetdeleteBTN' + (index + 1),
          "src": "/static/img/images/delete.png",
          "title": "Delete Meter"
        },
        on: {
          "click": function($event) {
            return _vm.deleteETHTBTN(index, inputItems)
          }
        }
      })])])
    }), 0) : _vm._e()]), _vm._v(" "), (_vm.meterCONFIGPageJSON.DATA.DLMSEthMetCfg.NumMeters == '0') ? _c('div', {
      staticClass: "text-center text-block"
    }, [_c('span', [_vm._v("No Records Found")])]) : _vm._e()])]
  ], 2)])])])]), _vm._v(" "), _c('li', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (_vm.meterCONFIGPageJSON.DATA.DLMSCfg.MeterType == 'Serial' && _vm.meterCONFIGPageJSON.DATA.DLMSCfg.FaultTolSupp == 'No'),
      expression: "meterCONFIGPageJSON.DATA.DLMSCfg.MeterType == 'Serial' && meterCONFIGPageJSON.DATA.DLMSCfg.FaultTolSupp == 'No'"
    }]
  }, [_c('i', {
    staticClass: "fa fa-sliders bg-yellow"
  }), _vm._v(" "), _c('div', {
    staticClass: "timeline-item"
  }, [_c('span', {
    staticClass: "time"
  }, [_vm._v(" ")]), _vm._v(" "), _c('h3', {
    staticClass: "timeline-header"
  }, [_vm._v("Configuration")]), _vm._v(" "), _c('div', {
    staticClass: "timeline-body"
  }, [_c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-12"
  }, [_vm._m(1), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
    staticClass: "col-lg-12"
  }, [_c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.instantaneousSERIALchekbox),
      expression: "instantaneousSERIALchekbox"
    }],
    attrs: {
      "type": "checkbox",
      "id": "instantaneousSERIALchekbox",
      "disabled": true
    },
    domProps: {
      "checked": Array.isArray(_vm.instantaneousSERIALchekbox) ? _vm._i(_vm.instantaneousSERIALchekbox, null) > -1 : (_vm.instantaneousSERIALchekbox)
    },
    on: {
      "change": function($event) {
        var $$a = _vm.instantaneousSERIALchekbox,
          $$el = $event.target,
          $$c = $$el.checked ? (true) : (false);
        if (Array.isArray($$a)) {
          var $$v = null,
            $$i = _vm._i($$a, $$v);
          if ($$el.checked) {
            $$i < 0 && (_vm.instantaneousSERIALchekbox = $$a.concat([$$v]))
          } else {
            $$i > -1 && (_vm.instantaneousSERIALchekbox = $$a.slice(0, $$i).concat($$a.slice($$i + 1)))
          }
        } else {
          _vm.instantaneousSERIALchekbox = $$c
        }
      }
    }
  }), _vm._v(" "), _c('label', {
    staticClass: "inputcheckTEXTLBLcss",
    attrs: {
      "for": "instantaneousSERIALchekbox"
    }
  }, [_vm._v("Instantaneous ")]), _vm._v("             \n                       "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.loadserveSERIALchekbox),
      expression: "loadserveSERIALchekbox"
    }],
    attrs: {
      "type": "checkbox",
      "id": "loadserveSERIALchekbox",
      "disabled": true
    },
    domProps: {
      "checked": Array.isArray(_vm.loadserveSERIALchekbox) ? _vm._i(_vm.loadserveSERIALchekbox, null) > -1 : (_vm.loadserveSERIALchekbox)
    },
    on: {
      "change": function($event) {
        var $$a = _vm.loadserveSERIALchekbox,
          $$el = $event.target,
          $$c = $$el.checked ? (true) : (false);
        if (Array.isArray($$a)) {
          var $$v = null,
            $$i = _vm._i($$a, $$v);
          if ($$el.checked) {
            $$i < 0 && (_vm.loadserveSERIALchekbox = $$a.concat([$$v]))
          } else {
            $$i > -1 && (_vm.loadserveSERIALchekbox = $$a.slice(0, $$i).concat($$a.slice($$i + 1)))
          }
        } else {
          _vm.loadserveSERIALchekbox = $$c
        }
      }
    }
  }), _vm._v(" "), _c('label', {
    staticClass: "inputcheckTEXTLBLcss",
    attrs: {
      "for": "loadserveSERIALchekbox"
    }
  }, [_vm._v("Load Survey ")]), _vm._v("             \n                        "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.eventdataSERIALchekbox),
      expression: "eventdataSERIALchekbox"
    }],
    attrs: {
      "type": "checkbox",
      "id": "eventdataSERIALchekbox",
      "disabled": true
    },
    domProps: {
      "checked": Array.isArray(_vm.eventdataSERIALchekbox) ? _vm._i(_vm.eventdataSERIALchekbox, null) > -1 : (_vm.eventdataSERIALchekbox)
    },
    on: {
      "change": function($event) {
        var $$a = _vm.eventdataSERIALchekbox,
          $$el = $event.target,
          $$c = $$el.checked ? (true) : (false);
        if (Array.isArray($$a)) {
          var $$v = null,
            $$i = _vm._i($$a, $$v);
          if ($$el.checked) {
            $$i < 0 && (_vm.eventdataSERIALchekbox = $$a.concat([$$v]))
          } else {
            $$i > -1 && (_vm.eventdataSERIALchekbox = $$a.slice(0, $$i).concat($$a.slice($$i + 1)))
          }
        } else {
          _vm.eventdataSERIALchekbox = $$c
        }
      }
    }
  }), _vm._v(" "), _c('label', {
    staticClass: "inputcheckTEXTLBLcss",
    attrs: {
      "for": "eventdataSERIALchekbox"
    }
  }, [_vm._v("Event Data ")]), _vm._v("             \n                        "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.midnightSERIALchekbox),
      expression: "midnightSERIALchekbox"
    }],
    attrs: {
      "type": "checkbox",
      "id": "midnightSERIALchekbox",
      "checked": "false"
    },
    domProps: {
      "checked": Array.isArray(_vm.midnightSERIALchekbox) ? _vm._i(_vm.midnightSERIALchekbox, null) > -1 : (_vm.midnightSERIALchekbox)
    },
    on: {
      "change": function($event) {
        var $$a = _vm.midnightSERIALchekbox,
          $$el = $event.target,
          $$c = $$el.checked ? (true) : (false);
        if (Array.isArray($$a)) {
          var $$v = null,
            $$i = _vm._i($$a, $$v);
          if ($$el.checked) {
            $$i < 0 && (_vm.midnightSERIALchekbox = $$a.concat([$$v]))
          } else {
            $$i > -1 && (_vm.midnightSERIALchekbox = $$a.slice(0, $$i).concat($$a.slice($$i + 1)))
          }
        } else {
          _vm.midnightSERIALchekbox = $$c
        }
      }
    }
  }), _vm._v(" "), _c('label', {
    staticClass: "inputcheckTEXTLBLcss",
    attrs: {
      "for": "midnightSERIALchekbox"
    }
  }, [_vm._v("Midnight ")]), _vm._v("      "), _c('i', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (_vm.midnightSERIALchekbox),
      expression: "midnightSERIALchekbox"
    }],
    staticClass: "fa fa-clock-o",
    attrs: {
      "aria-hidden": "true"
    }
  }), _vm._v(" "), _c('span', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (_vm.midnightSERIALchekbox),
      expression: "midnightSERIALchekbox"
    }],
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Poll Period ( in hours ) : ")]), _vm._v(" "), _c('select', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.midnightSERIALpollPeroidTXT),
      expression: "midnightSERIALpollPeroidTXT"
    }, {
      name: "show",
      rawName: "v-show",
      value: (_vm.midnightSERIALchekbox),
      expression: "midnightSERIALchekbox"
    }],
    staticClass: "inputTEXTcss",
    staticStyle: {
      "width": "100px"
    },
    on: {
      "change": function($event) {
        var $$selectedVal = Array.prototype.filter.call($event.target.options, function(o) {
          return o.selected
        }).map(function(o) {
          var val = "_value" in o ? o._value : o.value;
          return val
        });
        _vm.midnightSERIALpollPeroidTXT = $event.target.multiple ? $$selectedVal : $$selectedVal[0]
      }
    }
  }, [_c('option', {
    attrs: {
      "value": "1",
      "selected": ""
    }
  }, [_vm._v("1")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "2"
    }
  }, [_vm._v("2")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "4"
    }
  }, [_vm._v("4")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "6"
    }
  }, [_vm._v("6")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "12"
    }
  }, [_vm._v("12")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "24"
    }
  }, [_vm._v("24")])]), _vm._v("        \n                       "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.billingSERIALchekbox),
      expression: "billingSERIALchekbox"
    }],
    attrs: {
      "type": "checkbox",
      "id": "billingSERIALchekbox",
      "checked": "false"
    },
    domProps: {
      "checked": Array.isArray(_vm.billingSERIALchekbox) ? _vm._i(_vm.billingSERIALchekbox, null) > -1 : (_vm.billingSERIALchekbox)
    },
    on: {
      "change": function($event) {
        var $$a = _vm.billingSERIALchekbox,
          $$el = $event.target,
          $$c = $$el.checked ? (true) : (false);
        if (Array.isArray($$a)) {
          var $$v = null,
            $$i = _vm._i($$a, $$v);
          if ($$el.checked) {
            $$i < 0 && (_vm.billingSERIALchekbox = $$a.concat([$$v]))
          } else {
            $$i > -1 && (_vm.billingSERIALchekbox = $$a.slice(0, $$i).concat($$a.slice($$i + 1)))
          }
        } else {
          _vm.billingSERIALchekbox = $$c
        }
      }
    }
  }), _vm._v(" "), _c('label', {
    staticClass: "inputcheckTEXTLBLcss",
    attrs: {
      "for": "billingSERIALchekbox"
    }
  }, [_vm._v("Billing ")]), _vm._v("      "), _c('i', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (_vm.billingSERIALchekbox),
      expression: "billingSERIALchekbox"
    }],
    staticClass: "fa fa-clock-o",
    attrs: {
      "aria-hidden": "true"
    }
  }), _vm._v(" "), _c('span', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (_vm.billingSERIALchekbox),
      expression: "billingSERIALchekbox"
    }],
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Poll Period ( in hours ) : ")]), _vm._v(" "), _c('select', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.billingSERIALpollPeroidTXT),
      expression: "billingSERIALpollPeroidTXT"
    }, {
      name: "show",
      rawName: "v-show",
      value: (_vm.billingSERIALchekbox),
      expression: "billingSERIALchekbox"
    }],
    staticClass: "inputTEXTcss",
    staticStyle: {
      "width": "100px"
    },
    on: {
      "change": function($event) {
        var $$selectedVal = Array.prototype.filter.call($event.target.options, function(o) {
          return o.selected
        }).map(function(o) {
          var val = "_value" in o ? o._value : o.value;
          return val
        });
        _vm.billingSERIALpollPeroidTXT = $event.target.multiple ? $$selectedVal : $$selectedVal[0]
      }
    }
  }, [_c('option', {
    attrs: {
      "value": "1",
      "selected": ""
    }
  }, [_vm._v("1")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "2"
    }
  }, [_vm._v("2")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "4"
    }
  }, [_vm._v("4")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "6"
    }
  }, [_vm._v("6")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "12"
    }
  }, [_vm._v("12")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "24"
    }
  }, [_vm._v("24")])])]), _vm._v(" "), _c('p')])]), _vm._v(" "), _c('hr', {
    staticStyle: {
      "margin-top": "15px",
      "margin-bottom": "5px"
    }
  }), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-12"
  }, [_c('div', {
    staticClass: "tab",
    attrs: {
      "role": "tabpanel"
    }
  }, [_c('ul', {
    staticClass: "nav nav-tabs",
    attrs: {
      "role": "tablist"
    }
  }, _vm._l((parseInt(_vm.deviceCONFIGPageJSON.DATA.SerPortCfg.NumSerPorts)), function(index) {
    return _c('li', {
      key: index,
      class: [index == 1 ? 'active' : ''],
      attrs: {
        "role": "presentation",
        "id": 'portTab1' + index
      }
    }, [_c('a', {
      staticStyle: {
        "text-transform": "uppercase"
      },
      attrs: {
        "id": 'portTabbutton' + index,
        "href": '#portTabPANE' + index,
        "aria-controls": "home",
        "role": "tab",
        "data-toggle": "tab"
      }
    }, [_c('i', {
      staticClass: "fa fa-sliders iconbg",
      attrs: {
        "aria-hidden": "true"
      }
    }), _vm._v("   Port " + _vm._s(index) + "\n                        ")])])
  }), 0)]), _vm._v(" "), _c('div', {
    staticClass: "tab-content"
  }, _vm._l((parseInt(_vm.deviceCONFIGPageJSON.DATA.SerPortCfg.NumSerPorts)), function(indexx) {
    return _c('div', {
      key: indexx,
      staticClass: "tab-pane",
      class: [indexx == 1 ? 'active' : ''],
      attrs: {
        "role": "tabpanel",
        "aria-labelledby": 'portTabPANE' + indexx,
        "id": 'portTabPANE' + indexx
      }
    }, [_c('p'), _vm._v(" "), _c('h4', {
      staticClass: "timeline-header",
      staticStyle: {
        "text-decoration": "underline",
        "color": "#0073b7"
      }
    }, [_vm._v(" Port " + _vm._s(indexx) + " Configuration:")]), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', [_c('p'), _vm._v(" "), _c('div', {
      staticClass: "row"
    }, [_c('div', {
      staticClass: "col-md-12"
    }, [_vm._m(2, true), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
      staticClass: "row"
    }, [_c('div', {
      staticClass: "col-lg-2"
    }, [_c('span', {
      staticClass: "inputTEXTLBLcss"
    }, [_vm._v("Communication Mode : ")]), _vm._v(" "), _c('select', {
      staticClass: "inputTEXTcss",
      attrs: {
        "id": 'commModeDrpDwnID_serialportTabPANE' + indexx
      },
      on: {
        "click": _vm.saveMeterConfigPage
      }
    }, [_c('option', {
      attrs: {
        "value": "RS232_MODE",
        "selected": ""
      }
    }, [_vm._v("RS232 MODE")]), _vm._v(" "), _c('option', {
      attrs: {
        "value": "RS485_MODE"
      }
    }, [_vm._v("RS485 MODE")])])]), _vm._v(" "), _c('div', {
      staticClass: "col-lg-2"
    }, [_c('span', {
      staticClass: "inputTEXTLBLcss"
    }, [_vm._v("Baud Rate : ")]), _vm._v(" "), _c('select', {
      staticClass: "inputTEXTcss",
      attrs: {
        "id": 'baudrateeDrpDwnID_serialportTabPANE' + indexx
      },
      on: {
        "click": _vm.saveMeterConfigPage
      }
    }, [_c('option', {
      attrs: {
        "value": "2400",
        "selected": ""
      }
    }, [_vm._v("2400")]), _vm._v(" "), _c('option', {
      attrs: {
        "value": "4800"
      }
    }, [_vm._v("4800")]), _vm._v(" "), _c('option', {
      attrs: {
        "value": "9600"
      }
    }, [_vm._v("9600")]), _vm._v(" "), _c('option', {
      attrs: {
        "value": "19200"
      }
    }, [_vm._v("19200")]), _vm._v(" "), _c('option', {
      attrs: {
        "value": "38400"
      }
    }, [_vm._v("38400")]), _vm._v(" "), _c('option', {
      attrs: {
        "value": "57600"
      }
    }, [_vm._v("57600")]), _vm._v(" "), _c('option', {
      attrs: {
        "value": "115200"
      }
    }, [_vm._v("115200")])])]), _vm._v(" "), _c('div', {
      staticClass: "col-lg-1"
    }, [_c('span', {
      staticClass: "inputTEXTLBLcss"
    }, [_vm._v("Stop Bits : ")]), _vm._v(" "), _c('select', {
      staticClass: "inputTEXTcss",
      attrs: {
        "id": 'stopbitsDrpDwnID_serialportTabPANE' + indexx
      },
      on: {
        "click": _vm.saveMeterConfigPage
      }
    }, [_c('option', {
      attrs: {
        "value": "1",
        "selected": ""
      }
    }, [_vm._v("1")]), _vm._v(" "), _c('option', {
      attrs: {
        "value": "2"
      }
    }, [_vm._v("2")])])]), _vm._v(" "), _c('div', {
      staticClass: "col-lg-2"
    }, [_c('span', {
      staticClass: "inputTEXTLBLcss"
    }, [_vm._v("Parity : ")]), _vm._v(" "), _c('select', {
      staticClass: "inputTEXTcss",
      attrs: {
        "id": 'partyDrpDwnTID_serialportTabPANE' + indexx
      },
      on: {
        "click": _vm.saveMeterConfigPage
      }
    }, [_c('option', {
      attrs: {
        "value": "Even",
        "selected": ""
      }
    }, [_vm._v("Even")]), _vm._v(" "), _c('option', {
      attrs: {
        "value": "Odd"
      }
    }, [_vm._v("Odd")]), _vm._v(" "), _c('option', {
      attrs: {
        "value": "None"
      }
    }, [_vm._v("None")])])]), _vm._v(" "), _c('div', {
      staticClass: "col-lg-1"
    }, [_c('span', {
      staticClass: "inputTEXTLBLcss"
    }, [_vm._v("Data : ")]), _vm._v(" "), _c('select', {
      staticClass: "inputTEXTcss",
      attrs: {
        "id": 'databitsDrpDwnID_serialportTabPANE' + indexx
      },
      on: {
        "click": _vm.saveMeterConfigPage
      }
    }, [_c('option', {
      attrs: {
        "value": "7"
      }
    }, [_vm._v("7")]), _vm._v(" "), _c('option', {
      attrs: {
        "value": "8",
        "selected": ""
      }
    }, [_vm._v("8")])])]), _vm._v(" "), _c('div', {
      directives: [{
        name: "show",
        rawName: "v-show",
        value: (false),
        expression: "false"
      }],
      staticClass: "col-lg-2"
    }, [_c('span', {
      staticClass: "inputTEXTLBLcss"
    }, [_vm._v("Hand-Shake : ")]), _vm._v(" "), _c('select', {
      staticClass: "inputTEXTcss",
      attrs: {
        "id": 'handshakeDrpDwnID_serialportTabPANE' + indexx
      },
      on: {
        "click": _vm.saveMeterConfigPage
      }
    }, [_c('option', {
      attrs: {
        "value": "SW"
      }
    }, [_vm._v("Software")]), _vm._v(" "), _c('option', {
      attrs: {
        "value": "HW"
      }
    }, [_vm._v("Hardware")]), _vm._v(" "), _c('option', {
      attrs: {
        "value": "None",
        "selected": ""
      }
    }, [_vm._v("None")])])]), _vm._v(" "), _c('div', {
      staticClass: "col-lg-4 text-right"
    }, [_c('button', {
      staticClass: "btn btn-default",
      staticStyle: {
        "margin-top": "20px"
      },
      attrs: {
        "title": "Add Meter",
        "id": 'addmeter_serialportTabPANE' + indexx
      },
      on: {
        "click": function($event) {
          return _vm.addmeterSERIAL('addmeter_serialportTabPANE' + indexx, indexx)
        }
      }
    }, [_c('i', {
      staticClass: "fa fa-plus"
    }), _vm._v(" Add Meter")])])]), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
      staticClass: "row"
    }, [_c('div', {
      staticClass: "col-lg-12"
    }, [
      [_c('div', {
        staticClass: "table-responsive",
        staticStyle: {
          "border": "1px solid lightgray"
        },
        style: ({
          height: _vm.tableheight1
        }),
        attrs: {
          "id": 'meterconfigTablePane' + indexx
        }
      }, [_c('table', {
        staticClass: "table table-bordered table-responsive-stack",
        attrs: {
          "id": 'meterconfigTableID' + indexx
        }
      }, [_c('thead', {
        staticStyle: {
          "position": "sticky",
          "top": "-1px",
          "z-index": "1"
        }
      }, [_c('tr', [_c('th', [_vm._v("S.No")]), _vm._v(" "), _c('th', {
        directives: [{
          name: "show",
          rawName: "v-show",
          value: (false),
          expression: "false"
        }],
        staticStyle: {
          "width": "150px"
        }
      }, [_vm._v("Enable")]), _vm._v(" "), _c('th', [_vm._v("Meter Address")]), _vm._v(" "), _c('th', [_vm._v("Address Size")]), _vm._v(" "), _c('th', [_vm._v("Password")]), _vm._v(" "), _c('th', [_vm._v("Meter Location")]), _vm._v(" "), _c('th', [_vm._v("Timeout (in sec)")]), _vm._v(" "), _c('th', [_vm._v("Ret Count")]), _vm._v(" "), _c('th', [_vm._v("Delete")])])]), _vm._v(" "), (_vm.meterCONFIGPageJSON.DATA['DLMSP' + (indexx - 1) + 'MetCfg'].Meters.length != 0) ? _c('tbody', _vm._l((_vm.meterCONFIGPageJSON.DATA['DLMSP' + (indexx - 1) + 'MetCfg'].Meters), function(dlmsetersItems, dlmsBlockindex) {
        return _c('tr', {
          key: dlmsBlockindex
        }, [_c('td', [_vm._v(_vm._s(dlmsBlockindex + 1))]), _vm._v(" "), _c('td', {
          directives: [{
            name: "show",
            rawName: "v-show",
            value: (false),
            expression: "false"
          }],
          staticClass: "center-block text-center"
        }, [_c('input', {
          staticClass: "checkbox2",
          attrs: {
            "type": "checkbox",
            "id": 'portSERIALcheckbox' + 'DLMSP' + (indexx - 1) + 'MetCfg' + (dlmsBlockindex + 1)
          },
          domProps: {
            "checked": dlmsetersItems.Enable == '1' ? true : false
          },
          on: {
            "click": function($event) {
              _vm.enableSERIALMeterdevice($event, parseInt(indexx - 1), parseInt(dlmsBlockindex + 1), dlmsetersItems)
            }
          }
        })]), _vm._v(" "), _c('td', [_c('input', {
          staticClass: "inputTEXTcss center-block text-center",
          attrs: {
            "type": "text",
            "id": 'portSERIALaddress' + 'DLMSP' + (indexx - 1) + 'MetCfg' + (dlmsBlockindex + 1),
            "disabled": dlmsetersItems.Enable == '0' ? true : false
          },
          domProps: {
            "value": dlmsetersItems.Addr
          },
          on: {
            "change": function($event) {
              return _vm.saveMeterConfigPage()
            }
          }
        })]), _vm._v(" "), _c('td', [_c('select', {
          staticClass: "inputTEXTcss center-block text-center",
          attrs: {
            "id": 'portSERIALaddsize' + 'DLMSP' + (indexx - 1) + 'MetCfg' + (dlmsBlockindex + 1),
            "disabled": dlmsetersItems.Enable == '0' ? true : false
          },
          domProps: {
            "value": dlmsetersItems.AddrSz
          },
          on: {
            "change": function($event) {
              return _vm.saveMeterConfigPage()
            }
          }
        }, [_c('option', {
          attrs: {
            "value": "Choose Address Size",
            "selected": "",
            "disabled": ""
          }
        }, [_vm._v("Choose Address Size")]), _vm._v(" "), _vm._l((_vm.addressSZIEArray), function(items, index) {
          return _c('option', {
            key: index,
            domProps: {
              "value": items
            }
          }, [_vm._v(_vm._s(items))])
        })], 2)]), _vm._v(" "), _c('td', [_c('input', {
          staticClass: "inputTEXTcss center-block text-center",
          attrs: {
            "type": "password",
            "id": 'portSERIALPWD' + 'DLMSP' + (indexx - 1) + 'MetCfg' + (dlmsBlockindex + 1),
            "disabled": dlmsetersItems.Enable == '0' ? true : false
          },
          domProps: {
            "value": dlmsetersItems.Pwd
          },
          on: {
            "change": function($event) {
              return _vm.saveMeterConfigPage()
            }
          }
        })]), _vm._v(" "), _c('td', [_c('input', {
          staticClass: "inputTEXTcss center-block text-center",
          attrs: {
            "type": "text",
            "id": 'portSERIALLoc' + 'DLMSP' + (indexx - 1) + 'MetCfg' + (dlmsBlockindex + 1),
            "disabled": dlmsetersItems.Enable == '0' ? true : false
          },
          domProps: {
            "value": dlmsetersItems.Loc
          },
          on: {
            "change": function($event) {
              return _vm.saveMeterConfigPage()
            }
          }
        })]), _vm._v(" "), _c('td', [_c('select', {
          staticClass: "inputTEXTcss center-block text-center",
          attrs: {
            "id": 'portSERIALTo' + 'DLMSP' + (indexx - 1) + 'MetCfg' + (dlmsBlockindex + 1),
            "disabled": dlmsetersItems.Enable == '0' ? true : false
          },
          domProps: {
            "value": dlmsetersItems.TO
          },
          on: {
            "change": function($event) {
              return _vm.saveMeterConfigPage()
            }
          }
        }, [_c('option', {
          attrs: {
            "value": "Choose Count",
            "selected": "",
            "disabled": ""
          }
        }, [_vm._v("Choose Count")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "1"
          }
        }, [_vm._v("1")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "2"
          }
        }, [_vm._v("2")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "3"
          }
        }, [_vm._v("3")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "4"
          }
        }, [_vm._v("4")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "5"
          }
        }, [_vm._v("5")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "6"
          }
        }, [_vm._v("6")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "7"
          }
        }, [_vm._v("7")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "8"
          }
        }, [_vm._v("8")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "9"
          }
        }, [_vm._v("9")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "10"
          }
        }, [_vm._v("10")])])]), _vm._v(" "), _c('td', [_c('select', {
          staticClass: "inputTEXTcss center-block text-center",
          attrs: {
            "id": 'portSERIALRetCnt' + 'DLMSP' + (indexx - 1) + 'MetCfg' + (dlmsBlockindex + 1),
            "disabled": dlmsetersItems.Enable == '0' ? true : false
          },
          domProps: {
            "value": dlmsetersItems.RetCnt
          },
          on: {
            "change": function($event) {
              return _vm.saveMeterConfigPage()
            }
          }
        }, [_c('option', {
          attrs: {
            "value": "Choose Timeout",
            "selected": "",
            "disabled": ""
          }
        }, [_vm._v("Choose Timeout")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "1"
          }
        }, [_vm._v("1")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "2"
          }
        }, [_vm._v("2")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "3"
          }
        }, [_vm._v("3")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "4"
          }
        }, [_vm._v("4")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "5"
          }
        }, [_vm._v("5")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "6"
          }
        }, [_vm._v("6")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "7"
          }
        }, [_vm._v("7")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "8"
          }
        }, [_vm._v("8")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "9"
          }
        }, [_vm._v("9")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "10"
          }
        }, [_vm._v("10")])])]), _vm._v(" "), _c('td', [_c('img', {
          attrs: {
            "id": 'portSERIALdeleteBTN' + 'DLMSP' + (indexx - 1) + 'MetCfg' + (dlmsBlockindex + 1),
            "src": "/static/img/images/delete.png",
            "title": "Delete Meter"
          },
          on: {
            "click": function($event) {
              _vm.deleteSERIALBTN(dlmsBlockindex, (indexx - 1), dlmsetersItems)
            }
          }
        })])])
      }), 0) : _vm._e()]), _vm._v(" "), (parseInt(_vm.meterCONFIGPageJSON.DATA['DLMSP' + (indexx - 1) + 'MetCfg'].Meters.length) == 0) ? _c('div', {
        staticClass: "text-center text-block"
      }, [_c('span', [_vm._v("No Records Found")])]) : _vm._e()])]
    ], 2)])])])])])
  }), 0)])])])])]), _vm._v(" "), _c('li', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (_vm.meterCONFIGPageJSON.DATA.DLMSCfg.MeterType == 'Serial' && _vm.meterCONFIGPageJSON.DATA.DLMSCfg.FaultTolSupp == 'Yes'),
      expression: "meterCONFIGPageJSON.DATA.DLMSCfg.MeterType == 'Serial' && meterCONFIGPageJSON.DATA.DLMSCfg.FaultTolSupp == 'Yes'"
    }]
  }, [_c('i', {
    staticClass: "fa fa-sliders bg-yellow"
  }), _vm._v(" "), _c('div', {
    staticClass: "timeline-item"
  }, [_c('span', {
    staticClass: "time"
  }, [_vm._v(" ")]), _vm._v(" "), _c('h3', {
    staticClass: "timeline-header"
  }, [_vm._v("Configuration")]), _vm._v(" "), _c('div', {
    staticClass: "timeline-body"
  }, [_c('div', {
    staticClass: "col-lg-12"
  }, [_c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.instantaneousFAULTchekbox),
      expression: "instantaneousFAULTchekbox"
    }],
    attrs: {
      "type": "checkbox",
      "id": "instantaneousFAULTchekbox",
      "disabled": true
    },
    domProps: {
      "checked": Array.isArray(_vm.instantaneousFAULTchekbox) ? _vm._i(_vm.instantaneousFAULTchekbox, null) > -1 : (_vm.instantaneousFAULTchekbox)
    },
    on: {
      "change": function($event) {
        var $$a = _vm.instantaneousFAULTchekbox,
          $$el = $event.target,
          $$c = $$el.checked ? (true) : (false);
        if (Array.isArray($$a)) {
          var $$v = null,
            $$i = _vm._i($$a, $$v);
          if ($$el.checked) {
            $$i < 0 && (_vm.instantaneousFAULTchekbox = $$a.concat([$$v]))
          } else {
            $$i > -1 && (_vm.instantaneousFAULTchekbox = $$a.slice(0, $$i).concat($$a.slice($$i + 1)))
          }
        } else {
          _vm.instantaneousFAULTchekbox = $$c
        }
      }
    }
  }), _vm._v(" "), _c('label', {
    staticClass: "inputcheckTEXTLBLcss",
    attrs: {
      "for": "instantaneousFAULTchekbox"
    }
  }, [_vm._v("Instantaneous ")]), _vm._v("             \n                       "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.loadserveFAULTchekbox),
      expression: "loadserveFAULTchekbox"
    }],
    attrs: {
      "type": "checkbox",
      "id": "loadserveFAULTchekbox",
      "disabled": true
    },
    domProps: {
      "checked": Array.isArray(_vm.loadserveFAULTchekbox) ? _vm._i(_vm.loadserveFAULTchekbox, null) > -1 : (_vm.loadserveFAULTchekbox)
    },
    on: {
      "change": function($event) {
        var $$a = _vm.loadserveFAULTchekbox,
          $$el = $event.target,
          $$c = $$el.checked ? (true) : (false);
        if (Array.isArray($$a)) {
          var $$v = null,
            $$i = _vm._i($$a, $$v);
          if ($$el.checked) {
            $$i < 0 && (_vm.loadserveFAULTchekbox = $$a.concat([$$v]))
          } else {
            $$i > -1 && (_vm.loadserveFAULTchekbox = $$a.slice(0, $$i).concat($$a.slice($$i + 1)))
          }
        } else {
          _vm.loadserveFAULTchekbox = $$c
        }
      }
    }
  }), _vm._v(" "), _c('label', {
    staticClass: "inputcheckTEXTLBLcss",
    attrs: {
      "for": "loadserveFAULTchekbox"
    }
  }, [_vm._v("Load Survey ")]), _vm._v("             \n                        "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.eventdataFAULTchekbox),
      expression: "eventdataFAULTchekbox"
    }],
    attrs: {
      "type": "checkbox",
      "id": "eventdataFAULTchekbox",
      "disabled": true
    },
    domProps: {
      "checked": Array.isArray(_vm.eventdataFAULTchekbox) ? _vm._i(_vm.eventdataFAULTchekbox, null) > -1 : (_vm.eventdataFAULTchekbox)
    },
    on: {
      "change": function($event) {
        var $$a = _vm.eventdataFAULTchekbox,
          $$el = $event.target,
          $$c = $$el.checked ? (true) : (false);
        if (Array.isArray($$a)) {
          var $$v = null,
            $$i = _vm._i($$a, $$v);
          if ($$el.checked) {
            $$i < 0 && (_vm.eventdataFAULTchekbox = $$a.concat([$$v]))
          } else {
            $$i > -1 && (_vm.eventdataFAULTchekbox = $$a.slice(0, $$i).concat($$a.slice($$i + 1)))
          }
        } else {
          _vm.eventdataFAULTchekbox = $$c
        }
      }
    }
  }), _vm._v(" "), _c('label', {
    staticClass: "inputcheckTEXTLBLcss",
    attrs: {
      "for": "eventdataFAULTchekbox"
    }
  }, [_vm._v("Event Data ")]), _vm._v("             \n                        "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.midnightFAULTchekbox),
      expression: "midnightFAULTchekbox"
    }],
    attrs: {
      "type": "checkbox",
      "id": "midnightFAULTchekbox",
      "checked": "false"
    },
    domProps: {
      "checked": Array.isArray(_vm.midnightFAULTchekbox) ? _vm._i(_vm.midnightFAULTchekbox, null) > -1 : (_vm.midnightFAULTchekbox)
    },
    on: {
      "change": function($event) {
        var $$a = _vm.midnightFAULTchekbox,
          $$el = $event.target,
          $$c = $$el.checked ? (true) : (false);
        if (Array.isArray($$a)) {
          var $$v = null,
            $$i = _vm._i($$a, $$v);
          if ($$el.checked) {
            $$i < 0 && (_vm.midnightFAULTchekbox = $$a.concat([$$v]))
          } else {
            $$i > -1 && (_vm.midnightFAULTchekbox = $$a.slice(0, $$i).concat($$a.slice($$i + 1)))
          }
        } else {
          _vm.midnightFAULTchekbox = $$c
        }
      }
    }
  }), _vm._v(" "), _c('label', {
    staticClass: "inputcheckTEXTLBLcss",
    attrs: {
      "for": "midnightFAULTchekbox"
    }
  }, [_vm._v("Midnight ")]), _vm._v("     "), _c('i', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (_vm.midnightFAULTchekbox),
      expression: "midnightFAULTchekbox"
    }],
    staticClass: "fa fa-clock-o",
    attrs: {
      "aria-hidden": "true"
    }
  }), _vm._v(" "), _c('span', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (_vm.midnightFAULTchekbox),
      expression: "midnightFAULTchekbox"
    }],
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Poll Period ( in hours ) : ")]), _vm._v(" "), _c('select', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.midnightFAULTpollPeroidTXT),
      expression: "midnightFAULTpollPeroidTXT"
    }, {
      name: "show",
      rawName: "v-show",
      value: (_vm.midnightFAULTchekbox),
      expression: "midnightFAULTchekbox"
    }],
    staticClass: "inputTEXTcss",
    staticStyle: {
      "width": "100px"
    },
    on: {
      "change": function($event) {
        var $$selectedVal = Array.prototype.filter.call($event.target.options, function(o) {
          return o.selected
        }).map(function(o) {
          var val = "_value" in o ? o._value : o.value;
          return val
        });
        _vm.midnightFAULTpollPeroidTXT = $event.target.multiple ? $$selectedVal : $$selectedVal[0]
      }
    }
  }, [_c('option', {
    attrs: {
      "value": "1",
      "selected": ""
    }
  }, [_vm._v("1")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "2"
    }
  }, [_vm._v("2")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "4"
    }
  }, [_vm._v("4")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "6"
    }
  }, [_vm._v("6")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "12"
    }
  }, [_vm._v("12")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "24"
    }
  }, [_vm._v("24")])]), _vm._v("        \n                       "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.billingFAULTchekbox),
      expression: "billingFAULTchekbox"
    }],
    attrs: {
      "type": "checkbox",
      "id": "billingFAULTchekbox",
      "checked": "false"
    },
    domProps: {
      "checked": Array.isArray(_vm.billingFAULTchekbox) ? _vm._i(_vm.billingFAULTchekbox, null) > -1 : (_vm.billingFAULTchekbox)
    },
    on: {
      "change": function($event) {
        var $$a = _vm.billingFAULTchekbox,
          $$el = $event.target,
          $$c = $$el.checked ? (true) : (false);
        if (Array.isArray($$a)) {
          var $$v = null,
            $$i = _vm._i($$a, $$v);
          if ($$el.checked) {
            $$i < 0 && (_vm.billingFAULTchekbox = $$a.concat([$$v]))
          } else {
            $$i > -1 && (_vm.billingFAULTchekbox = $$a.slice(0, $$i).concat($$a.slice($$i + 1)))
          }
        } else {
          _vm.billingFAULTchekbox = $$c
        }
      }
    }
  }), _vm._v(" "), _c('label', {
    staticClass: "inputcheckTEXTLBLcss",
    attrs: {
      "for": "billingFAULTchekbox"
    }
  }, [_vm._v("Billing ")]), _vm._v("     "), _c('i', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (_vm.billingFAULTchekbox),
      expression: "billingFAULTchekbox"
    }],
    staticClass: "fa fa-clock-o",
    attrs: {
      "aria-hidden": "true"
    }
  }), _vm._v(" "), _c('span', {
    directives: [{
      name: "show",
      rawName: "v-show",
      value: (_vm.billingFAULTchekbox),
      expression: "billingFAULTchekbox"
    }],
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Poll Period ( in hours ) : ")]), _vm._v(" "), _c('select', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.billingFAULTpollPeroidTXT),
      expression: "billingFAULTpollPeroidTXT"
    }, {
      name: "show",
      rawName: "v-show",
      value: (_vm.billingFAULTchekbox),
      expression: "billingFAULTchekbox"
    }],
    staticClass: "inputTEXTcss",
    staticStyle: {
      "width": "100px"
    },
    on: {
      "change": function($event) {
        var $$selectedVal = Array.prototype.filter.call($event.target.options, function(o) {
          return o.selected
        }).map(function(o) {
          var val = "_value" in o ? o._value : o.value;
          return val
        });
        _vm.billingFAULTpollPeroidTXT = $event.target.multiple ? $$selectedVal : $$selectedVal[0]
      }
    }
  }, [_c('option', {
    attrs: {
      "value": "1",
      "selected": ""
    }
  }, [_vm._v("1")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "2"
    }
  }, [_vm._v("2")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "4"
    }
  }, [_vm._v("4")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "6"
    }
  }, [_vm._v("6")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "12"
    }
  }, [_vm._v("12")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "24"
    }
  }, [_vm._v("24")])])]), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-12"
  }, [_c('div', {
    staticClass: "tab",
    attrs: {
      "role": "tabpanel"
    }
  }, [_c('ul', {
    staticClass: "nav nav-tabs",
    attrs: {
      "role": "tablist"
    }
  }, _vm._l((parseInt(_vm.deviceCONFIGPageJSON.DATA.SerPortCfg.NumSerPorts)), function(index) {
    return _c('li', {
      key: index,
      class: [index == 1 ? 'active' : ''],
      attrs: {
        "role": "presentation",
        "id": 'portTab1' + index
      }
    }, [_c('a', {
      staticStyle: {
        "text-transform": "uppercase"
      },
      attrs: {
        "id": 'portTabbutton' + index,
        "href": '#portFaultTabPANE' + index,
        "aria-controls": "home",
        "role": "tab",
        "data-toggle": "tab"
      }
    }, [_c('i', {
      staticClass: "fa fa-sliders iconbg",
      attrs: {
        "aria-hidden": "true"
      }
    }), _vm._v("   Ring " + _vm._s(index) + "\n                        ")])])
  }), 0)]), _vm._v(" "), _c('div', {
    staticClass: "tab-content"
  }, _vm._l((parseInt(_vm.deviceCONFIGPageJSON.DATA.SerPortCfg.NumSerPorts)), function(indexx) {
    return _c('div', {
      key: indexx,
      staticClass: "tab-pane",
      class: [indexx == 1 ? 'active' : ''],
      attrs: {
        "role": "tabpanel",
        "aria-labelledby": 'portFaultTabPANE' + indexx,
        "id": 'portFaultTabPANE' + indexx
      }
    }, [_c('p'), _vm._v(" "), _c('h4', {
      staticClass: "timeline-header",
      staticStyle: {
        "text-decoration": "underline",
        "color": "#0073b7"
      }
    }, [_vm._v(" Ring " + _vm._s(indexx) + " Configuration:")]), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', [_c('p'), _vm._v(" "), _c('div', {
      staticClass: "row"
    }, [_c('div', {
      staticClass: "col-md-12"
    }, [_vm._m(3, true), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
      staticClass: "row"
    }, [_c('div', {
      staticClass: "col-lg-2"
    }, [_c('span', {
      staticClass: "inputTEXTLBLcss"
    }, [_vm._v("Communication Mode : ")]), _vm._v(" "), _c('select', {
      staticClass: "inputTEXTcss",
      attrs: {
        "id": 'commModeDrpDwnID_faultportTabPANE' + indexx
      },
      on: {
        "click": _vm.saveMeterConfigPage
      }
    }, [_c('option', {
      attrs: {
        "value": "RS232_MODE",
        "selected": ""
      }
    }, [_vm._v("RS232 MODE")]), _vm._v(" "), _c('option', {
      attrs: {
        "value": "RS485_MODE"
      }
    }, [_vm._v("RS485 MODE")])])]), _vm._v(" "), _c('div', {
      staticClass: "col-lg-2"
    }, [_c('span', {
      staticClass: "inputTEXTLBLcss"
    }, [_vm._v("Baud Rate : ")]), _vm._v(" "), _c('select', {
      staticClass: "inputTEXTcss",
      attrs: {
        "id": 'baudrateeDrpDwnID_faultportTabPANE' + indexx
      },
      on: {
        "click": _vm.saveMeterConfigPage
      }
    }, [_c('option', {
      attrs: {
        "value": "2400",
        "selected": ""
      }
    }, [_vm._v("2400")]), _vm._v(" "), _c('option', {
      attrs: {
        "value": "4800"
      }
    }, [_vm._v("4800")]), _vm._v(" "), _c('option', {
      attrs: {
        "value": "9600"
      }
    }, [_vm._v("9600")]), _vm._v(" "), _c('option', {
      attrs: {
        "value": "19200"
      }
    }, [_vm._v("19200")]), _vm._v(" "), _c('option', {
      attrs: {
        "value": "38400"
      }
    }, [_vm._v("38400")]), _vm._v(" "), _c('option', {
      attrs: {
        "value": "57600"
      }
    }, [_vm._v("57600")]), _vm._v(" "), _c('option', {
      attrs: {
        "value": "115200"
      }
    }, [_vm._v("115200")])])]), _vm._v(" "), _c('div', {
      staticClass: "col-lg-1"
    }, [_c('span', {
      staticClass: "inputTEXTLBLcss"
    }, [_vm._v("Stop Bits : ")]), _vm._v(" "), _c('select', {
      staticClass: "inputTEXTcss",
      attrs: {
        "id": 'stopbitsDrpDwnID_faultportTabPANE' + indexx
      },
      on: {
        "click": _vm.saveMeterConfigPage
      }
    }, [_c('option', {
      attrs: {
        "value": "1",
        "selected": ""
      }
    }, [_vm._v("1")]), _vm._v(" "), _c('option', {
      attrs: {
        "value": "2"
      }
    }, [_vm._v("2")])])]), _vm._v(" "), _c('div', {
      staticClass: "col-lg-2"
    }, [_c('span', {
      staticClass: "inputTEXTLBLcss"
    }, [_vm._v("Parity : ")]), _vm._v(" "), _c('select', {
      staticClass: "inputTEXTcss",
      attrs: {
        "id": 'partyDrpDwnTID_faultportTabPANE' + indexx
      },
      on: {
        "click": _vm.saveMeterConfigPage
      }
    }, [_c('option', {
      attrs: {
        "value": "Even",
        "selected": ""
      }
    }, [_vm._v("Even")]), _vm._v(" "), _c('option', {
      attrs: {
        "value": "Odd"
      }
    }, [_vm._v("Odd")]), _vm._v(" "), _c('option', {
      attrs: {
        "value": "None"
      }
    }, [_vm._v("None")])])]), _vm._v(" "), _c('div', {
      staticClass: "col-lg-1"
    }, [_c('span', {
      staticClass: "inputTEXTLBLcss"
    }, [_vm._v("Data : ")]), _vm._v(" "), _c('select', {
      staticClass: "inputTEXTcss",
      attrs: {
        "id": 'databitsDrpDwnID_faultportTabPANE' + indexx
      },
      on: {
        "click": _vm.saveMeterConfigPage
      }
    }, [_c('option', {
      attrs: {
        "value": "7"
      }
    }, [_vm._v("7")]), _vm._v(" "), _c('option', {
      attrs: {
        "value": "8",
        "selected": ""
      }
    }, [_vm._v("8")])])]), _vm._v(" "), _c('div', {
      directives: [{
        name: "show",
        rawName: "v-show",
        value: (false),
        expression: "false"
      }],
      staticClass: "col-lg-2"
    }, [_c('span', {
      staticClass: "inputTEXTLBLcss"
    }, [_vm._v("Hand-Shake : ")]), _vm._v(" "), _c('select', {
      staticClass: "inputTEXTcss",
      attrs: {
        "id": 'handshakeDrpDwnID_faultportTabPANE' + indexx
      },
      on: {
        "click": _vm.saveMeterConfigPage
      }
    }, [_c('option', {
      attrs: {
        "value": "SW"
      }
    }, [_vm._v("Software")]), _vm._v(" "), _c('option', {
      attrs: {
        "value": "HW"
      }
    }, [_vm._v("Hardware")]), _vm._v(" "), _c('option', {
      attrs: {
        "value": "None",
        "selected": ""
      }
    }, [_vm._v("None")])])]), _vm._v(" "), _c('div', {
      staticClass: "col-lg-4 text-right"
    }, [_c('button', {
      staticClass: "btn btn-default",
      staticStyle: {
        "margin-top": "20px"
      },
      attrs: {
        "title": "Add Meter",
        "id": 'addmeter_faultportTabPANE' + indexx
      },
      on: {
        "click": function($event) {
          return _vm.addmeterFAULT('addmeter_faultportTabPANE' + indexx, indexx)
        }
      }
    }, [_c('i', {
      staticClass: "fa fa-plus"
    }), _vm._v(" Add Meter")])])]), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
      staticClass: "row"
    }, [_c('div', {
      staticClass: "col-lg-12"
    }, [
      [_c('div', {
        staticClass: "table-responsive",
        staticStyle: {
          "border": "1px solid lightgray"
        },
        style: ({
          height: _vm.tableheight1
        }),
        attrs: {
          "id": 'meterfalutconfigTablePane' + indexx
        }
      }, [_c('table', {
        staticClass: "table table-bordered table-responsive-stack",
        attrs: {
          "id": 'meterfalutconfigTableID' + indexx
        }
      }, [_c('thead', {
        staticStyle: {
          "position": "sticky",
          "top": "-1px",
          "z-index": "1"
        }
      }, [_c('tr', [_c('th', [_vm._v("S.No")]), _vm._v(" "), _c('th', {
        directives: [{
          name: "show",
          rawName: "v-show",
          value: (false),
          expression: "false"
        }],
        staticStyle: {
          "width": "150px"
        }
      }, [_vm._v("Enable")]), _vm._v(" "), _c('th', [_vm._v("Meter IP Address")]), _vm._v(" "), _c('th', [_vm._v("AddrType")]), _vm._v(" "), _c('th', [_vm._v("Password")]), _vm._v(" "), _c('th', [_vm._v("Meter Location")]), _vm._v(" "), _c('th', [_vm._v("Timeout (in sec)")]), _vm._v(" "), _c('th', [_vm._v("Ret Count")]), _vm._v(" "), _c('th', [_vm._v("Delete")])])]), _vm._v(" "), (_vm.meterCONFIGPageJSON.DATA['DLMSP' + (indexx - 1) + 'MetCfg'].Meters.length != 0) ? _c('tbody', _vm._l((_vm.meterCONFIGPageJSON.DATA['DLMSP' + (indexx - 1) + 'MetCfg'].Meters), function(dlmsetersItems, dlmsBlockindex) {
        return _c('tr', {
          key: dlmsBlockindex
        }, [_c('td', [_vm._v(_vm._s(dlmsBlockindex + 1))]), _vm._v(" "), _c('td', {
          directives: [{
            name: "show",
            rawName: "v-show",
            value: (false),
            expression: "false"
          }],
          staticClass: "center-block text-center"
        }, [_c('input', {
          staticClass: "checkbox2",
          attrs: {
            "type": "checkbox",
            "id": 'portFAULTcheckbox' + 'DLMSP' + (indexx - 1) + 'MetCfg' + (dlmsBlockindex + 1)
          },
          domProps: {
            "checked": dlmsetersItems.Enable == '1' ? true : false
          },
          on: {
            "click": function($event) {
              _vm.enableFAULTdevice($event, parseInt(indexx - 1), parseInt(dlmsBlockindex + 1), dlmsetersItems)
            }
          }
        })]), _vm._v(" "), _c('td', [_c('input', {
          staticClass: "inputTEXTcss center-block text-center",
          attrs: {
            "type": "text",
            "id": 'portFAULTaddr' + 'DLMSP' + (indexx - 1) + 'MetCfg' + (dlmsBlockindex + 1),
            "disabled": dlmsetersItems.Enable == '0' ? true : false
          },
          domProps: {
            "value": dlmsetersItems.Addr
          },
          on: {
            "change": function($event) {
              return _vm.saveMeterConfigPage()
            }
          }
        })]), _vm._v(" "), _c('td', [_c('input', {
          staticClass: "inputTEXTcss center-block text-center",
          attrs: {
            "type": "text",
            "id": 'portFAULTAddrType' + 'DLMSP' + (indexx - 1) + 'MetCfg' + (dlmsBlockindex + 1),
            "disabled": dlmsetersItems.Enable == '0' ? true : false
          },
          domProps: {
            "value": dlmsetersItems.AddrType
          },
          on: {
            "change": function($event) {
              return _vm.saveMeterConfigPage()
            }
          }
        })]), _vm._v(" "), _c('td', [_c('input', {
          staticClass: "inputTEXTcss center-block text-center",
          attrs: {
            "type": "password",
            "id": 'portFAULTPwd' + 'DLMSP' + (indexx - 1) + 'MetCfg' + (dlmsBlockindex + 1),
            "disabled": dlmsetersItems.Enable == '0' ? true : false
          },
          domProps: {
            "value": dlmsetersItems.Pwd
          },
          on: {
            "change": function($event) {
              return _vm.saveMeterConfigPage()
            }
          }
        })]), _vm._v(" "), _c('td', [_c('input', {
          staticClass: "inputTEXTcss center-block text-center",
          attrs: {
            "type": "text",
            "id": 'portFAULTLoc' + 'DLMSP' + (indexx - 1) + 'MetCfg' + (dlmsBlockindex + 1),
            "disabled": dlmsetersItems.Enable == '0' ? true : false
          },
          domProps: {
            "value": dlmsetersItems.Loc
          },
          on: {
            "change": function($event) {
              return _vm.saveMeterConfigPage()
            }
          }
        })]), _vm._v(" "), _c('td', [_c('select', {
          staticClass: "inputTEXTcss center-block text-center",
          attrs: {
            "id": 'portFAULTTO' + 'DLMSP' + (indexx - 1) + 'MetCfg' + (dlmsBlockindex + 1),
            "disabled": dlmsetersItems.Enable == '0' ? true : false
          },
          domProps: {
            "value": dlmsetersItems.TO
          },
          on: {
            "change": function($event) {
              return _vm.saveMeterConfigPage()
            }
          }
        }, [_c('option', {
          attrs: {
            "value": "Choose Timeout",
            "selected": "",
            "disabled": ""
          }
        }, [_vm._v("Choose Timeout")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "1"
          }
        }, [_vm._v("1")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "2"
          }
        }, [_vm._v("2")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "3"
          }
        }, [_vm._v("3")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "4"
          }
        }, [_vm._v("4")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "5"
          }
        }, [_vm._v("5")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "6"
          }
        }, [_vm._v("6")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "7"
          }
        }, [_vm._v("7")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "8"
          }
        }, [_vm._v("8")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "9"
          }
        }, [_vm._v("9")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "10"
          }
        }, [_vm._v("10")])])]), _vm._v(" "), _c('td', [_c('select', {
          staticClass: "inputTEXTcss center-block text-center",
          attrs: {
            "id": 'portFAULTRetCnt' + 'DLMSP' + (indexx - 1) + 'MetCfg' + (dlmsBlockindex + 1),
            "disabled": dlmsetersItems.Enable == '0' ? true : false
          },
          domProps: {
            "value": dlmsetersItems.RetCnt
          },
          on: {
            "change": function($event) {
              return _vm.saveMeterConfigPage()
            }
          }
        }, [_c('option', {
          attrs: {
            "value": "Choose Count",
            "selected": "",
            "disabled": ""
          }
        }, [_vm._v("Choose Count")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "1"
          }
        }, [_vm._v("1")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "2"
          }
        }, [_vm._v("2")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "3"
          }
        }, [_vm._v("3")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "4"
          }
        }, [_vm._v("4")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "5"
          }
        }, [_vm._v("5")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "6"
          }
        }, [_vm._v("6")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "7"
          }
        }, [_vm._v("7")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "8"
          }
        }, [_vm._v("8")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "9"
          }
        }, [_vm._v("9")]), _vm._v(" "), _c('option', {
          attrs: {
            "value": "10"
          }
        }, [_vm._v("10")])])]), _vm._v(" "), _c('td', [_c('img', {
          attrs: {
            "id": 'portFAULTdeleteBTN' + 'DLMSP' + (indexx - 1) + 'MetCfg' + (dlmsBlockindex + 1),
            "src": "/static/img/images/delete.png",
            "title": "Delete Meter"
          },
          on: {
            "click": function($event) {
              _vm.deleteFAULTBTN(dlmsBlockindex, (indexx - 1), dlmsetersItems)
            }
          }
        })])])
      }), 0) : _vm._e()]), _vm._v(" "), (parseInt(_vm.meterCONFIGPageJSON.DATA['DLMSP' + (indexx - 1) + 'MetCfg'].Meters.length) == 0) ? _c('div', {
        staticClass: "text-center text-block"
      }, [_c('span', [_vm._v("No Records Found")])]) : _vm._e()])]
    ], 2)])])])])])
  }), 0)])])])])])])])])], 1)
},staticRenderFns: [function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('h4', [_c('p', [_vm._v("Data Poll Configuration")])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('h5', [_c('b', [_vm._v("Data Poll Configuration")])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('h5', [_c('b', [_vm._v("Serial Configuration")])])
},function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('h5', [_c('b', [_vm._v("Serial Configuration")])])
}]}

/***/ }),
/* 139 */
/***/ (function(module, exports) {

module.exports={render:function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('section', {
    staticClass: "content",
    attrs: {
      "id": "UpstreamConfigPagePANE"
    }
  }, [_c('vue-element-loading', {
    attrs: {
      "active": _vm.isLoading,
      "spinner": "spinner",
      "color": "#000",
      "is-full-screen": true
    }
  }), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-12"
  }, [_c('ul', {
    staticClass: "timeline"
  }, [_c('li', [_c('i', {
    staticClass: "fa fa-cogs"
  }), _vm._v(" "), _c('div', {
    staticClass: "timeline-item"
  }, [_c('h3', {
    staticClass: "timeline-header"
  }, [_vm._v("IEC-104 Settings            \n                       "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.iec104Enablechekbox),
      expression: "iec104Enablechekbox"
    }],
    attrs: {
      "type": "checkbox",
      "id": "iec104Enablechekbox"
    },
    domProps: {
      "checked": Array.isArray(_vm.iec104Enablechekbox) ? _vm._i(_vm.iec104Enablechekbox, null) > -1 : (_vm.iec104Enablechekbox)
    },
    on: {
      "change": function($event) {
        var $$a = _vm.iec104Enablechekbox,
          $$el = $event.target,
          $$c = $$el.checked ? (true) : (false);
        if (Array.isArray($$a)) {
          var $$v = null,
            $$i = _vm._i($$a, $$v);
          if ($$el.checked) {
            $$i < 0 && (_vm.iec104Enablechekbox = $$a.concat([$$v]))
          } else {
            $$i > -1 && (_vm.iec104Enablechekbox = $$a.slice(0, $$i).concat($$a.slice($$i + 1)))
          }
        } else {
          _vm.iec104Enablechekbox = $$c
        }
      }
    }
  }), _vm._v(" "), _c('label', {
    staticClass: "inputcheckTEXTLBLcss",
    attrs: {
      "for": "iec104Enablechekbox"
    }
  }, [_vm._v("Enable ")])]), _vm._v(" "), _c('div', {
    staticClass: "timeline-body"
  }, [_c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Station Address : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.iecStationTXT),
      expression: "iecStationTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "iecStationTXT",
      "placeholder": "Station Address",
      "maxlength": "32",
      "disabled": !_vm.iec104Enablechekbox
    },
    domProps: {
      "value": (_vm.iecStationTXT)
    },
    on: {
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.iecStationTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Port Number :")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.iecportTXT),
      expression: "iecportTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "iecportTXT",
      "placeholder": "Port Number",
      "maxlength": "5",
      "disabled": !_vm.iec104Enablechekbox
    },
    domProps: {
      "value": (_vm.iecportTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "keypress": _vm.isNumber,
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.iecportTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Cyclic Int(in Sec) : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.iecCylicTXT),
      expression: "iecCylicTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "iecCylicTXT",
      "placeholder": "Cyclic Int(in Sec)",
      "disabled": !_vm.iec104Enablechekbox
    },
    domProps: {
      "value": (_vm.iecCylicTXT)
    },
    on: {
      "keypress": _vm.isNumber,
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.iecCylicTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Start IOA Addr : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.startIOAaddTXT),
      expression: "startIOAaddTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "startIOAaddTXT",
      "placeholder": "Start IOA Addr",
      "disabled": !_vm.iec104Enablechekbox
    },
    domProps: {
      "value": (_vm.startIOAaddTXT)
    },
    on: {
      "keypress": _vm.isNumber,
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.startIOAaddTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("COT Size : ")]), _vm._v(" "), _c('select', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.iecCodsizedwnTXT),
      expression: "iecCodsizedwnTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "iecCodsizedwnTXT",
      "disabled": !_vm.iec104Enablechekbox
    },
    on: {
      "change": function($event) {
        var $$selectedVal = Array.prototype.filter.call($event.target.options, function(o) {
          return o.selected
        }).map(function(o) {
          var val = "_value" in o ? o._value : o.value;
          return val
        });
        _vm.iecCodsizedwnTXT = $event.target.multiple ? $$selectedVal : $$selectedVal[0]
      }
    }
  }, [_c('option', {
    attrs: {
      "value": "Choose COT Size",
      "selected": "",
      "disabled": ""
    }
  }, [_vm._v("Choose COT Size")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "1"
    }
  }, [_vm._v("1")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "2"
    }
  }, [_vm._v("2")])])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("IOA Size :             ")]), _vm._v(" "), _c('select', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.iecIOAsizedwnTXT),
      expression: "iecIOAsizedwnTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "iecIOAsizedwnTXT",
      "disabled": !_vm.iec104Enablechekbox
    },
    on: {
      "change": function($event) {
        var $$selectedVal = Array.prototype.filter.call($event.target.options, function(o) {
          return o.selected
        }).map(function(o) {
          var val = "_value" in o ? o._value : o.value;
          return val
        });
        _vm.iecIOAsizedwnTXT = $event.target.multiple ? $$selectedVal : $$selectedVal[0]
      }
    }
  }, [_c('option', {
    attrs: {
      "value": "Choose IOA Size",
      "selected": "",
      "disabled": ""
    }
  }, [_vm._v("Choose IOA Size")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "3"
    }
  }, [_vm._v("3")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "2"
    }
  }, [_vm._v("2")])])])]), _vm._v(" "), _c('div', {
    staticStyle: {
      "height": "15px"
    }
  }), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-12"
  }, [_c('h4', {
    staticClass: "timeline-header"
  }, [_vm._v("Allowed Master Settings             \n                       "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.allowMastercheckbox),
      expression: "allowMastercheckbox"
    }],
    attrs: {
      "type": "checkbox",
      "id": "allowMastercheckbox"
    },
    domProps: {
      "checked": Array.isArray(_vm.allowMastercheckbox) ? _vm._i(_vm.allowMastercheckbox, null) > -1 : (_vm.allowMastercheckbox)
    },
    on: {
      "change": function($event) {
        var $$a = _vm.allowMastercheckbox,
          $$el = $event.target,
          $$c = $$el.checked ? (true) : (false);
        if (Array.isArray($$a)) {
          var $$v = null,
            $$i = _vm._i($$a, $$v);
          if ($$el.checked) {
            $$i < 0 && (_vm.allowMastercheckbox = $$a.concat([$$v]))
          } else {
            $$i > -1 && (_vm.allowMastercheckbox = $$a.slice(0, $$i).concat($$a.slice($$i + 1)))
          }
        } else {
          _vm.allowMastercheckbox = $$c
        }
      }
    }
  }), _vm._v(" "), _c('label', {
    staticClass: "inputcheckTEXTLBLcss",
    attrs: {
      "for": "allowMastercheckbox"
    }
  }, [_vm._v("Enable ")])])])]), _vm._v(" "), _c('div', {
    staticStyle: {
      "height": "10px"
    }
  }), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-3"
  }, [_c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.allowMastercheckbox1),
      expression: "allowMastercheckbox1"
    }],
    attrs: {
      "type": "checkbox",
      "id": "allowMastercheckbox1",
      "disabled": !_vm.allowMastercheckbox
    },
    domProps: {
      "checked": Array.isArray(_vm.allowMastercheckbox1) ? _vm._i(_vm.allowMastercheckbox1, null) > -1 : (_vm.allowMastercheckbox1)
    },
    on: {
      "change": function($event) {
        var $$a = _vm.allowMastercheckbox1,
          $$el = $event.target,
          $$c = $$el.checked ? (true) : (false);
        if (Array.isArray($$a)) {
          var $$v = null,
            $$i = _vm._i($$a, $$v);
          if ($$el.checked) {
            $$i < 0 && (_vm.allowMastercheckbox1 = $$a.concat([$$v]))
          } else {
            $$i > -1 && (_vm.allowMastercheckbox1 = $$a.slice(0, $$i).concat($$a.slice($$i + 1)))
          }
        } else {
          _vm.allowMastercheckbox1 = $$c
        }
      }
    }
  }), _vm._v("  \n                 "), _c('label', {
    staticClass: "inputcheckTEXTLBLcss",
    attrs: {
      "for": "allowMastercheckbox1"
    }
  }, [_vm._v("Allowed Master1  ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.allowMasterTXT1),
      expression: "allowMasterTXT1"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "allowMasterTXT1",
      "placeholder": "Allowed Master1 Address",
      "maxlength": "32",
      "disabled": !_vm.allowMastercheckbox1 || !_vm.allowMastercheckbox
    },
    domProps: {
      "value": (_vm.allowMasterTXT1)
    },
    on: {
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.allowMasterTXT1 = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-3"
  }, [_c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.allowMastercheckbox2),
      expression: "allowMastercheckbox2"
    }],
    attrs: {
      "type": "checkbox",
      "id": "allowMastercheckbox2",
      "disabled": !_vm.allowMastercheckbox
    },
    domProps: {
      "checked": Array.isArray(_vm.allowMastercheckbox2) ? _vm._i(_vm.allowMastercheckbox2, null) > -1 : (_vm.allowMastercheckbox2)
    },
    on: {
      "change": function($event) {
        var $$a = _vm.allowMastercheckbox2,
          $$el = $event.target,
          $$c = $$el.checked ? (true) : (false);
        if (Array.isArray($$a)) {
          var $$v = null,
            $$i = _vm._i($$a, $$v);
          if ($$el.checked) {
            $$i < 0 && (_vm.allowMastercheckbox2 = $$a.concat([$$v]))
          } else {
            $$i > -1 && (_vm.allowMastercheckbox2 = $$a.slice(0, $$i).concat($$a.slice($$i + 1)))
          }
        } else {
          _vm.allowMastercheckbox2 = $$c
        }
      }
    }
  }), _vm._v("  \n                        "), _c('label', {
    staticClass: "inputcheckTEXTLBLcss",
    attrs: {
      "for": "allowMastercheckbox2"
    }
  }, [_vm._v("Allowed Master2 :  ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.allowMasterTXT2),
      expression: "allowMasterTXT2"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "allowMasterTXT2",
      "placeholder": "Allowed Master2 Address",
      "maxlength": "32",
      "disabled": !_vm.allowMastercheckbox2 || !_vm.allowMastercheckbox
    },
    domProps: {
      "value": (_vm.allowMasterTXT2)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "keypress": _vm.isNumber,
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.allowMasterTXT2 = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-3"
  }, [_c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.allowMastercheckbox3),
      expression: "allowMastercheckbox3"
    }],
    attrs: {
      "type": "checkbox",
      "id": "allowMastercheckbox3",
      "disabled": !_vm.allowMastercheckbox
    },
    domProps: {
      "checked": Array.isArray(_vm.allowMastercheckbox3) ? _vm._i(_vm.allowMastercheckbox3, null) > -1 : (_vm.allowMastercheckbox3)
    },
    on: {
      "change": function($event) {
        var $$a = _vm.allowMastercheckbox3,
          $$el = $event.target,
          $$c = $$el.checked ? (true) : (false);
        if (Array.isArray($$a)) {
          var $$v = null,
            $$i = _vm._i($$a, $$v);
          if ($$el.checked) {
            $$i < 0 && (_vm.allowMastercheckbox3 = $$a.concat([$$v]))
          } else {
            $$i > -1 && (_vm.allowMastercheckbox3 = $$a.slice(0, $$i).concat($$a.slice($$i + 1)))
          }
        } else {
          _vm.allowMastercheckbox3 = $$c
        }
      }
    }
  }), _vm._v("  \n                         "), _c('label', {
    staticClass: "inputcheckTEXTLBLcss",
    attrs: {
      "for": "allowMastercheckbox3"
    }
  }, [_vm._v("Allowed Master3 :  ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.allowMasterTXT3),
      expression: "allowMasterTXT3"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "allowMasterTXT3",
      "placeholder": "Allowed Master3 Address",
      "maxlength": "32",
      "disabled": !_vm.allowMastercheckbox3 || !_vm.allowMastercheckbox
    },
    domProps: {
      "value": (_vm.allowMasterTXT3)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "keypress": _vm.isNumber,
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.allowMasterTXT3 = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-3"
  }, [_c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.allowMastercheckbox4),
      expression: "allowMastercheckbox4"
    }],
    attrs: {
      "type": "checkbox",
      "id": "allowMastercheckbox4",
      "disabled": !_vm.allowMastercheckbox
    },
    domProps: {
      "checked": Array.isArray(_vm.allowMastercheckbox4) ? _vm._i(_vm.allowMastercheckbox4, null) > -1 : (_vm.allowMastercheckbox4)
    },
    on: {
      "change": function($event) {
        var $$a = _vm.allowMastercheckbox4,
          $$el = $event.target,
          $$c = $$el.checked ? (true) : (false);
        if (Array.isArray($$a)) {
          var $$v = null,
            $$i = _vm._i($$a, $$v);
          if ($$el.checked) {
            $$i < 0 && (_vm.allowMastercheckbox4 = $$a.concat([$$v]))
          } else {
            $$i > -1 && (_vm.allowMastercheckbox4 = $$a.slice(0, $$i).concat($$a.slice($$i + 1)))
          }
        } else {
          _vm.allowMastercheckbox4 = $$c
        }
      }
    }
  }), _vm._v("  \n                      "), _c('label', {
    staticClass: "inputcheckTEXTLBLcss",
    attrs: {
      "for": "allowMastercheckbox4"
    }
  }, [_vm._v("Allowed Master4 :  ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.allowMasterTXT4),
      expression: "allowMasterTXT4"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "allowMasterTXT4",
      "placeholder": "Allowed Master4 Address",
      "maxlength": "32",
      "disabled": !_vm.allowMastercheckbox4 || !_vm.allowMastercheckbox
    },
    domProps: {
      "value": (_vm.allowMasterTXT4)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "keypress": _vm.isNumber,
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.allowMasterTXT4 = $event.target.value
      }
    }
  })])]), _vm._v(" "), _c('p')])])]), _vm._v(" "), _c('li', [_c('i', {
    staticClass: "fa fa-cogs"
  }), _vm._v(" "), _c('div', {
    staticClass: "timeline-item"
  }, [_c('h3', {
    staticClass: "timeline-header"
  }, [_vm._v("FTP Server Settings            \n                       "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.ftpEnablechekbox),
      expression: "ftpEnablechekbox"
    }],
    attrs: {
      "type": "checkbox",
      "id": "ftpEnablechekbox"
    },
    domProps: {
      "checked": Array.isArray(_vm.ftpEnablechekbox) ? _vm._i(_vm.ftpEnablechekbox, null) > -1 : (_vm.ftpEnablechekbox)
    },
    on: {
      "change": function($event) {
        var $$a = _vm.ftpEnablechekbox,
          $$el = $event.target,
          $$c = $$el.checked ? (true) : (false);
        if (Array.isArray($$a)) {
          var $$v = null,
            $$i = _vm._i($$a, $$v);
          if ($$el.checked) {
            $$i < 0 && (_vm.ftpEnablechekbox = $$a.concat([$$v]))
          } else {
            $$i > -1 && (_vm.ftpEnablechekbox = $$a.slice(0, $$i).concat($$a.slice($$i + 1)))
          }
        } else {
          _vm.ftpEnablechekbox = $$c
        }
      }
    }
  }), _vm._v(" "), _c('label', {
    staticClass: "inputcheckTEXTLBLcss",
    attrs: {
      "for": "ftpEnablechekbox"
    }
  }, [_vm._v("Enable ")]), _vm._v("                        \n                     "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.ftpLOGEnablechekbox),
      expression: "ftpLOGEnablechekbox"
    }],
    attrs: {
      "type": "checkbox",
      "id": "ftpLOGEnablechekbox",
      "disabled": !_vm.ftpEnablechekbox
    },
    domProps: {
      "checked": Array.isArray(_vm.ftpLOGEnablechekbox) ? _vm._i(_vm.ftpLOGEnablechekbox, null) > -1 : (_vm.ftpLOGEnablechekbox)
    },
    on: {
      "change": function($event) {
        var $$a = _vm.ftpLOGEnablechekbox,
          $$el = $event.target,
          $$c = $$el.checked ? (true) : (false);
        if (Array.isArray($$a)) {
          var $$v = null,
            $$i = _vm._i($$a, $$v);
          if ($$el.checked) {
            $$i < 0 && (_vm.ftpLOGEnablechekbox = $$a.concat([$$v]))
          } else {
            $$i > -1 && (_vm.ftpLOGEnablechekbox = $$a.slice(0, $$i).concat($$a.slice($$i + 1)))
          }
        } else {
          _vm.ftpLOGEnablechekbox = $$c
        }
      }
    }
  }), _vm._v(" "), _c('label', {
    staticClass: "inputcheckTEXTLBLcss",
    attrs: {
      "for": "ftpLOGEnablechekbox"
    }
  }, [_vm._v("Server Log Enable ")])]), _vm._v(" "), _c('div', {
    staticClass: "timeline-body"
  }, [_c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("IP Address : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.ftpIpaddTXT),
      expression: "ftpIpaddTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "ftpIpaddTXT",
      "placeholder": "IP Address",
      "maxlength": "32",
      "disabled": !_vm.ftpEnablechekbox
    },
    domProps: {
      "value": (_vm.ftpIpaddTXT)
    },
    on: {
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.ftpIpaddTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Port Number : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.ftpprtnoTXT),
      expression: "ftpprtnoTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "ftpprtnoTXT",
      "placeholder": "Port Number",
      "maxlength": "5",
      "disabled": !_vm.ftpEnablechekbox
    },
    domProps: {
      "value": (_vm.ftpprtnoTXT)
    },
    on: {
      "keypress": _vm.isNumber,
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.ftpprtnoTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("User Name : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.ftpusernameTXT),
      expression: "ftpusernameTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "ftpusernameTXT",
      "placeholder": "User Name",
      "maxlength": "10",
      "disabled": !_vm.ftpEnablechekbox
    },
    domProps: {
      "value": (_vm.ftpusernameTXT)
    },
    on: {
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.ftpusernameTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Password :             ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.ftppasswordTXT),
      expression: "ftppasswordTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "ftppasswordTXT",
      "placeholder": "Password",
      "maxlength": "32",
      "disabled": !_vm.ftpEnablechekbox
    },
    domProps: {
      "value": (_vm.ftppasswordTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.ftppasswordTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Directory : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.ftpdirTXT),
      expression: "ftpdirTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "ftpdirTXT",
      "placeholder": "Directory",
      "disabled": !_vm.ftpEnablechekbox
    },
    domProps: {
      "value": (_vm.ftpdirTXT)
    },
    on: {
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.ftpdirTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Time Interval(mins) : ")]), _vm._v(" "), _c('select', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.ftptimeoutTXT),
      expression: "ftptimeoutTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "name": "ftpTimeInt",
      "id": "ftpTimeInt",
      "disabled": !_vm.ftpEnablechekbox
    },
    on: {
      "change": function($event) {
        var $$selectedVal = Array.prototype.filter.call($event.target.options, function(o) {
          return o.selected
        }).map(function(o) {
          var val = "_value" in o ? o._value : o.value;
          return val
        });
        _vm.ftptimeoutTXT = $event.target.multiple ? $$selectedVal : $$selectedVal[0]
      }
    }
  }, [_c('option', {
    attrs: {
      "value": "15",
      "selected": ""
    }
  }, [_vm._v("15")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "30"
    }
  }, [_vm._v("30")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "60"
    }
  }, [_vm._v("60")])])])]), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Log IP Address : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.ftpLOGIpaddTXT),
      expression: "ftpLOGIpaddTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "ftpLOGIpaddTXT",
      "placeholder": "IP Address",
      "maxlength": "32",
      "disabled": !_vm.ftpLOGEnablechekbox
    },
    domProps: {
      "value": (_vm.ftpLOGIpaddTXT)
    },
    on: {
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.ftpLOGIpaddTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Log Port Number : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.ftpLOGprtnoTXT),
      expression: "ftpLOGprtnoTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "ftpLOGprtnoTXT",
      "placeholder": "Port Number",
      "maxlength": "5",
      "disabled": !_vm.ftpLOGEnablechekbox
    },
    domProps: {
      "value": (_vm.ftpLOGprtnoTXT)
    },
    on: {
      "keypress": _vm.isNumber,
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.ftpLOGprtnoTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Log User Name : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.ftpLOGusernameTXT),
      expression: "ftpLOGusernameTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "ftpLOGusernameTXT",
      "placeholder": "User Name",
      "maxlength": "10",
      "disabled": !_vm.ftpLOGEnablechekbox
    },
    domProps: {
      "value": (_vm.ftpLOGusernameTXT)
    },
    on: {
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.ftpLOGusernameTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Log Password :             ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.ftpLOGpasswordTXT),
      expression: "ftpLOGpasswordTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "ftpLOGpasswordTXT",
      "placeholder": "Password",
      "maxlength": "32",
      "disabled": !_vm.ftpLOGEnablechekbox
    },
    domProps: {
      "value": (_vm.ftpLOGpasswordTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.ftpLOGpasswordTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Log Directory : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.ftpLOGdirTXT),
      expression: "ftpLOGdirTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "ftpLOGdirTXT",
      "placeholder": "Directory",
      "disabled": !_vm.ftpLOGEnablechekbox
    },
    domProps: {
      "value": (_vm.ftpLOGdirTXT)
    },
    on: {
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.ftpLOGdirTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Log Time Interval(mins) : ")]), _vm._v(" "), _c('select', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.ftpLOGtimeoutTXT),
      expression: "ftpLOGtimeoutTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "name": "ftpLOGTimeInt",
      "id": "ftpLOGTimeInt",
      "disabled": !_vm.ftpLOGEnablechekbox
    },
    on: {
      "change": function($event) {
        var $$selectedVal = Array.prototype.filter.call($event.target.options, function(o) {
          return o.selected
        }).map(function(o) {
          var val = "_value" in o ? o._value : o.value;
          return val
        });
        _vm.ftpLOGtimeoutTXT = $event.target.multiple ? $$selectedVal : $$selectedVal[0]
      }
    }
  }, [_c('option', {
    attrs: {
      "value": "15",
      "selected": ""
    }
  }, [_vm._v("15")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "30"
    }
  }, [_vm._v("30")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "60"
    }
  }, [_vm._v("60")])])])])])])]), _vm._v(" "), _c('li', [_c('i', {
    staticClass: "fa fa-cogs"
  }), _vm._v(" "), _c('div', {
    staticClass: "timeline-item"
  }, [_c('h3', {
    staticClass: "timeline-header"
  }, [_vm._v("Mod TCP Settings            \n                       "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.modTcpEnablechekbox),
      expression: "modTcpEnablechekbox"
    }],
    attrs: {
      "type": "checkbox",
      "id": "modTcpEnablechekbox"
    },
    domProps: {
      "checked": Array.isArray(_vm.modTcpEnablechekbox) ? _vm._i(_vm.modTcpEnablechekbox, null) > -1 : (_vm.modTcpEnablechekbox)
    },
    on: {
      "change": function($event) {
        var $$a = _vm.modTcpEnablechekbox,
          $$el = $event.target,
          $$c = $$el.checked ? (true) : (false);
        if (Array.isArray($$a)) {
          var $$v = null,
            $$i = _vm._i($$a, $$v);
          if ($$el.checked) {
            $$i < 0 && (_vm.modTcpEnablechekbox = $$a.concat([$$v]))
          } else {
            $$i > -1 && (_vm.modTcpEnablechekbox = $$a.slice(0, $$i).concat($$a.slice($$i + 1)))
          }
        } else {
          _vm.modTcpEnablechekbox = $$c
        }
      }
    }
  }), _vm._v(" "), _c('label', {
    staticClass: "inputcheckTEXTLBLcss",
    attrs: {
      "for": "modTcpEnablechekbox"
    }
  }, [_vm._v("Enable ")])]), _vm._v(" "), _c('div', {
    staticClass: "timeline-body"
  }, [_c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Modbus Device Id : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.modTCPdeVidTXT),
      expression: "modTCPdeVidTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "modTCPdeVidTXT",
      "placeholder": "Modbus Device Id",
      "disabled": !_vm.modTcpEnablechekbox
    },
    domProps: {
      "value": (_vm.modTCPdeVidTXT)
    },
    on: {
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.modTCPdeVidTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("RespToAllSlaveId : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.RespToAllSlaveIdTXT),
      expression: "RespToAllSlaveIdTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "RespToAllSlaveIdTXT",
      "placeholder": "RespToAllSlaveId",
      "maxlength": "5",
      "disabled": !_vm.modTcpEnablechekbox
    },
    domProps: {
      "value": (_vm.RespToAllSlaveIdTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.RespToAllSlaveIdTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Port Number : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.modTCPprtnoTXT),
      expression: "modTCPprtnoTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "modTCPprtnoTXT",
      "placeholder": "Port Number",
      "maxlength": "5",
      "disabled": !_vm.modTcpEnablechekbox
    },
    domProps: {
      "value": (_vm.modTCPprtnoTXT)
    },
    on: {
      "keypress": _vm.isNumber,
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.modTCPprtnoTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Hold Register Start Address : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.modTCPholdstartAddTXT),
      expression: "modTCPholdstartAddTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "modTCPholdstartAddTXT",
      "placeholder": "Hold Register Start Address",
      "maxlength": "5",
      "disabled": !_vm.modTcpEnablechekbox
    },
    domProps: {
      "value": (_vm.modTCPholdstartAddTXT)
    },
    on: {
      "keypress": _vm.isNumber,
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.modTCPholdstartAddTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Input Register Start Address : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.modTCPinputstartAddTXT),
      expression: "modTCPinputstartAddTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "modTCPinputstartAddTXT",
      "placeholder": "Input Register Start Address",
      "disabled": !_vm.modTcpEnablechekbox
    },
    domProps: {
      "value": (_vm.modTCPinputstartAddTXT)
    },
    on: {
      "keypress": _vm.isNumber,
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.modTCPinputstartAddTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Discrite Input Start Address : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.modTCPDiscriteinputstartAddTXT),
      expression: "modTCPDiscriteinputstartAddTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "modTCPDiscriteinputstartAddTXT",
      "placeholder": "Discrite Input Start Address",
      "disabled": !_vm.modTcpEnablechekbox
    },
    domProps: {
      "value": (_vm.modTCPDiscriteinputstartAddTXT)
    },
    on: {
      "keypress": _vm.isNumber,
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.modTCPDiscriteinputstartAddTXT = $event.target.value
      }
    }
  })])]), _vm._v(" "), _c('p')])])]), _vm._v(" "), _c('li', [_c('i', {
    staticClass: "fa fa-cogs"
  }), _vm._v(" "), _c('div', {
    staticClass: "timeline-item"
  }, [_c('h3', {
    staticClass: "timeline-header"
  }, [_vm._v("MQTT Settings            \n                       "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.mqttEnablecheckbox),
      expression: "mqttEnablecheckbox"
    }],
    attrs: {
      "type": "checkbox",
      "id": "mqttEnablecheckbox"
    },
    domProps: {
      "checked": Array.isArray(_vm.mqttEnablecheckbox) ? _vm._i(_vm.mqttEnablecheckbox, null) > -1 : (_vm.mqttEnablecheckbox)
    },
    on: {
      "change": function($event) {
        var $$a = _vm.mqttEnablecheckbox,
          $$el = $event.target,
          $$c = $$el.checked ? (true) : (false);
        if (Array.isArray($$a)) {
          var $$v = null,
            $$i = _vm._i($$a, $$v);
          if ($$el.checked) {
            $$i < 0 && (_vm.mqttEnablecheckbox = $$a.concat([$$v]))
          } else {
            $$i > -1 && (_vm.mqttEnablecheckbox = $$a.slice(0, $$i).concat($$a.slice($$i + 1)))
          }
        } else {
          _vm.mqttEnablecheckbox = $$c
        }
      }
    }
  }), _vm._v(" "), _c('label', {
    staticClass: "inputcheckTEXTLBLcss",
    attrs: {
      "for": "mqttEnablecheckbox"
    }
  }, [_vm._v("Enable ")])]), _vm._v(" "), _c('div', {
    staticClass: "timeline-body"
  }, [_c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Broker Ip : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.mqttBrokerIpTXT),
      expression: "mqttBrokerIpTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "mqttBrokerIpTXT",
      "placeholder": "Broker Ip",
      "disabled": !_vm.mqttEnablecheckbox
    },
    domProps: {
      "value": (_vm.mqttBrokerIpTXT)
    },
    on: {
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.mqttBrokerIpTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Port Number : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.mqttBrokerPortTXT),
      expression: "mqttBrokerPortTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "mqttBrokerPortTXT",
      "placeholder": "Port Number",
      "maxlength": "5",
      "disabled": !_vm.mqttEnablecheckbox
    },
    domProps: {
      "value": (_vm.mqttBrokerPortTXT)
    },
    on: {
      "keypress": _vm.isNumber,
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.mqttBrokerPortTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("User Name : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.mqttBrokerUserNameTXT),
      expression: "mqttBrokerUserNameTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "mqttBrokerUserNameTXT",
      "placeholder": "User Name",
      "disabled": !_vm.mqttEnablecheckbox
    },
    domProps: {
      "value": (_vm.mqttBrokerUserNameTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.mqttBrokerUserNameTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Password : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.mqttBrokerPasswordTXT),
      expression: "mqttBrokerPasswordTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "mqttBrokerPasswordTXT",
      "placeholder": "Password",
      "disabled": !_vm.mqttEnablecheckbox
    },
    domProps: {
      "value": (_vm.mqttBrokerPasswordTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.mqttBrokerPasswordTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Cyclic Data Topic : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.mqttBrokerCycDataTopicTXT),
      expression: "mqttBrokerCycDataTopicTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "mqttBrokerCycDataTopicTXT",
      "placeholder": "Cyclic Data Topic",
      "disabled": !_vm.mqttEnablecheckbox
    },
    domProps: {
      "value": (_vm.mqttBrokerCycDataTopicTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.mqttBrokerCycDataTopicTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Cmd Topic : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.mqttBrokerCmdTopicTXT),
      expression: "mqttBrokerCmdTopicTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "mqttBrokerCmdTopicTXT",
      "placeholder": "Cmd Topic",
      "disabled": !_vm.mqttEnablecheckbox
    },
    domProps: {
      "value": (_vm.mqttBrokerCmdTopicTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.mqttBrokerCmdTopicTXT = $event.target.value
      }
    }
  })])]), _vm._v(" "), _c('p'), _vm._v(" "), _c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-2",
    staticStyle: {
      "margin-top": "25px",
      "text-align": "center"
    }
  }, [_c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.mqttEnableEventTopicTXT),
      expression: "mqttEnableEventTopicTXT"
    }],
    attrs: {
      "type": "checkbox",
      "id": "mqttEnableEventTopicTXT",
      "disabled": !_vm.mqttEnablecheckbox
    },
    domProps: {
      "checked": Array.isArray(_vm.mqttEnableEventTopicTXT) ? _vm._i(_vm.mqttEnableEventTopicTXT, null) > -1 : (_vm.mqttEnableEventTopicTXT)
    },
    on: {
      "change": function($event) {
        var $$a = _vm.mqttEnableEventTopicTXT,
          $$el = $event.target,
          $$c = $$el.checked ? (true) : (false);
        if (Array.isArray($$a)) {
          var $$v = null,
            $$i = _vm._i($$a, $$v);
          if ($$el.checked) {
            $$i < 0 && (_vm.mqttEnableEventTopicTXT = $$a.concat([$$v]))
          } else {
            $$i > -1 && (_vm.mqttEnableEventTopicTXT = $$a.slice(0, $$i).concat($$a.slice($$i + 1)))
          }
        } else {
          _vm.mqttEnableEventTopicTXT = $$c
        }
      }
    }
  }), _vm._v(" "), _c('label', {
    staticClass: "inputcheckTEXTLBLcss",
    attrs: {
      "for": "mqttEnableEventTopicTXT"
    }
  }, [_vm._v("Event Enable ")])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Event Topic : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.mqttEventTopicTXT),
      expression: "mqttEventTopicTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "mqttEventTopicTXT",
      "placeholder": "Event Topic",
      "disabled": !_vm.mqttEnableEventTopicTXT || !_vm.mqttEnablecheckbox
    },
    domProps: {
      "value": (_vm.mqttEventTopicTXT)
    },
    on: {
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.mqttEventTopicTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2",
    staticStyle: {
      "margin-top": "25px",
      "text-align": "center"
    }
  }, [_c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.mqttEnableDiagTopicTXT),
      expression: "mqttEnableDiagTopicTXT"
    }],
    attrs: {
      "type": "checkbox",
      "id": "mqttEnableDiagTopicTXT",
      "disabled": !_vm.mqttEnablecheckbox
    },
    domProps: {
      "checked": Array.isArray(_vm.mqttEnableDiagTopicTXT) ? _vm._i(_vm.mqttEnableDiagTopicTXT, null) > -1 : (_vm.mqttEnableDiagTopicTXT)
    },
    on: {
      "change": function($event) {
        var $$a = _vm.mqttEnableDiagTopicTXT,
          $$el = $event.target,
          $$c = $$el.checked ? (true) : (false);
        if (Array.isArray($$a)) {
          var $$v = null,
            $$i = _vm._i($$a, $$v);
          if ($$el.checked) {
            $$i < 0 && (_vm.mqttEnableDiagTopicTXT = $$a.concat([$$v]))
          } else {
            $$i > -1 && (_vm.mqttEnableDiagTopicTXT = $$a.slice(0, $$i).concat($$a.slice($$i + 1)))
          }
        } else {
          _vm.mqttEnableDiagTopicTXT = $$c
        }
      }
    }
  }), _vm._v(" "), _c('label', {
    staticClass: "inputcheckTEXTLBLcss",
    attrs: {
      "for": "mqttEnableDiagTopicTXT"
    }
  }, [_vm._v("Diag Enable ")])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Diag Topic : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.mqttDiagTopicTXT),
      expression: "mqttDiagTopicTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "mqttDiagTopicTXT",
      "placeholder": "User Name",
      "disabled": !_vm.mqttEnableDiagTopicTXT || !_vm.mqttEnablecheckbox
    },
    domProps: {
      "value": (_vm.mqttDiagTopicTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.mqttDiagTopicTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Cyclic Period : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.mqttPeriodTXT),
      expression: "mqttPeriodTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "mqttPeriodTXT",
      "placeholder": "User Name",
      "disabled": !_vm.mqttEnablecheckbox
    },
    domProps: {
      "value": (_vm.mqttPeriodTXT)
    },
    on: {
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.mqttPeriodTXT = $event.target.value
      }
    }
  })])])])])]), _vm._v(" "), _c('li', [_c('i', {
    staticClass: "fa fa-cogs"
  }), _vm._v(" "), _c('div', {
    staticClass: "timeline-item"
  }, [_c('h3', {
    staticClass: "timeline-header"
  }, [_vm._v("CMS EMS Settings            \n                       "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.cmsEMSEnablecheckbox),
      expression: "cmsEMSEnablecheckbox"
    }],
    attrs: {
      "type": "checkbox",
      "id": "cmsEMSEnablecheckbox"
    },
    domProps: {
      "checked": Array.isArray(_vm.cmsEMSEnablecheckbox) ? _vm._i(_vm.cmsEMSEnablecheckbox, null) > -1 : (_vm.cmsEMSEnablecheckbox)
    },
    on: {
      "change": function($event) {
        var $$a = _vm.cmsEMSEnablecheckbox,
          $$el = $event.target,
          $$c = $$el.checked ? (true) : (false);
        if (Array.isArray($$a)) {
          var $$v = null,
            $$i = _vm._i($$a, $$v);
          if ($$el.checked) {
            $$i < 0 && (_vm.cmsEMSEnablecheckbox = $$a.concat([$$v]))
          } else {
            $$i > -1 && (_vm.cmsEMSEnablecheckbox = $$a.slice(0, $$i).concat($$a.slice($$i + 1)))
          }
        } else {
          _vm.cmsEMSEnablecheckbox = $$c
        }
      }
    }
  }), _vm._v(" "), _c('label', {
    staticClass: "inputcheckTEXTLBLcss",
    attrs: {
      "for": "cmsEMSEnablecheckbox"
    }
  }, [_vm._v("Enable ")])]), _vm._v(" "), _c('div', {
    staticClass: "timeline-body"
  }, [_c('div', {
    staticClass: "row"
  }, [_c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Ip Address : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.cmsemsEnableIPTXT),
      expression: "cmsemsEnableIPTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "modTCPdeVidTXT",
      "placeholder": "Ip Address",
      "disabled": !_vm.cmsEMSEnablecheckbox
    },
    domProps: {
      "value": (_vm.cmsemsEnableIPTXT)
    },
    on: {
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.cmsemsEnableIPTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Port No : ")]), _vm._v(" "), _c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.cmsemsEnableportNoTXT),
      expression: "cmsemsEnableportNoTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "id": "RespToAllSlaveIdTXT",
      "placeholder": "Port No",
      "maxlength": "5",
      "disabled": !_vm.cmsEMSEnablecheckbox
    },
    domProps: {
      "value": (_vm.cmsemsEnableportNoTXT)
    },
    on: {
      "keypress": _vm.isNumber,
      "keydown": function($event) {
        if (!$event.type.indexOf('key') && _vm._k($event.keyCode, "space", 32, $event.key, [" ", "Spacebar"])) { return null; }
        $event.preventDefault();
      },
      "input": function($event) {
        if ($event.target.composing) { return; }
        _vm.cmsemsEnableportNoTXT = $event.target.value
      }
    }
  })]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2",
    staticStyle: {
      "margin-top": "25px",
      "text-align": "center"
    }
  }, [_c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.cmsemsEnableEvent),
      expression: "cmsemsEnableEvent"
    }],
    attrs: {
      "type": "checkbox",
      "id": "dbgEnablecheckbox",
      "disabled": !_vm.cmsEMSEnablecheckbox
    },
    domProps: {
      "checked": Array.isArray(_vm.cmsemsEnableEvent) ? _vm._i(_vm.cmsemsEnableEvent, null) > -1 : (_vm.cmsemsEnableEvent)
    },
    on: {
      "change": function($event) {
        var $$a = _vm.cmsemsEnableEvent,
          $$el = $event.target,
          $$c = $$el.checked ? (true) : (false);
        if (Array.isArray($$a)) {
          var $$v = null,
            $$i = _vm._i($$a, $$v);
          if ($$el.checked) {
            $$i < 0 && (_vm.cmsemsEnableEvent = $$a.concat([$$v]))
          } else {
            $$i > -1 && (_vm.cmsemsEnableEvent = $$a.slice(0, $$i).concat($$a.slice($$i + 1)))
          }
        } else {
          _vm.cmsemsEnableEvent = $$c
        }
      }
    }
  }), _vm._v(" "), _c('label', {
    staticClass: "inputcheckTEXTLBLcss",
    attrs: {
      "for": "dbgEnablecheckbox"
    }
  }, [_vm._v("Enable Event ")])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2",
    staticStyle: {
      "margin-top": "25px",
      "text-align": "center"
    }
  }, [_c('input', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.cmsemsEnableDiag),
      expression: "cmsemsEnableDiag"
    }],
    attrs: {
      "type": "checkbox",
      "id": "dbgEnablediagcheckbox",
      "disabled": !_vm.cmsEMSEnablecheckbox
    },
    domProps: {
      "checked": Array.isArray(_vm.cmsemsEnableDiag) ? _vm._i(_vm.cmsemsEnableDiag, null) > -1 : (_vm.cmsemsEnableDiag)
    },
    on: {
      "change": function($event) {
        var $$a = _vm.cmsemsEnableDiag,
          $$el = $event.target,
          $$c = $$el.checked ? (true) : (false);
        if (Array.isArray($$a)) {
          var $$v = null,
            $$i = _vm._i($$a, $$v);
          if ($$el.checked) {
            $$i < 0 && (_vm.cmsemsEnableDiag = $$a.concat([$$v]))
          } else {
            $$i > -1 && (_vm.cmsemsEnableDiag = $$a.slice(0, $$i).concat($$a.slice($$i + 1)))
          }
        } else {
          _vm.cmsemsEnableDiag = $$c
        }
      }
    }
  }), _vm._v(" "), _c('label', {
    staticClass: "inputcheckTEXTLBLcss",
    attrs: {
      "for": "dbgEnablediagcheckbox"
    }
  }, [_vm._v("Enable Diag ")])]), _vm._v(" "), _c('div', {
    staticClass: "col-lg-2"
  }, [_c('span', {
    staticClass: "inputTEXTLBLcss"
  }, [_vm._v("Cyclic Period : ")]), _vm._v(" "), _c('select', {
    directives: [{
      name: "model",
      rawName: "v-model",
      value: (_vm.cmsemsPeriodTXT),
      expression: "cmsemsPeriodTXT"
    }],
    staticClass: "inputTEXTcss",
    attrs: {
      "name": "cmsemsPeriod",
      "id": "cmsemsPeriodid",
      "disabled": !_vm.cmsEMSEnablecheckbox
    },
    on: {
      "change": function($event) {
        var $$selectedVal = Array.prototype.filter.call($event.target.options, function(o) {
          return o.selected
        }).map(function(o) {
          var val = "_value" in o ? o._value : o.value;
          return val
        });
        _vm.cmsemsPeriodTXT = $event.target.multiple ? $$selectedVal : $$selectedVal[0]
      }
    }
  }, [_c('option', {
    attrs: {
      "value": "15",
      "selected": ""
    }
  }, [_vm._v("15")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "30"
    }
  }, [_vm._v("30")]), _vm._v(" "), _c('option', {
    attrs: {
      "value": "60"
    }
  }, [_vm._v("60")])])])]), _vm._v(" "), _c('p')])])])])])])], 1)
},staticRenderFns: []}

/***/ }),
/* 140 */
/***/ (function(module, exports) {

module.exports={render:function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('div', {
    class: ['wrapper', _vm.classes]
  }, [_c('dash-header'), _vm._v(" "), _c('sidebar', {
    ref: "sidebar"
  }), _vm._v(" "), _c('div', {
    staticClass: "content-wrapper"
  }, [_c('section', {
    staticClass: "content-header"
  }, [_c('h1', {
    staticStyle: {
      "color": "#0073b7"
    }
  }, [_vm._v("\n        " + _vm._s(_vm.$route.name) + "\n        "), _c('small', [_vm._v(_vm._s(_vm.$route.meta.description))])])]), _vm._v(" "), _c('router-view')], 1), _vm._v(" "), _c('dash-footer')], 1)
},staticRenderFns: []}

/***/ })
],[24]);
//# sourceMappingURL=app.daa2400775146ea0dc9d.js.map