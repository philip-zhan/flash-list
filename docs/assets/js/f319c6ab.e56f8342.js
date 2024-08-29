"use strict";(self.webpackChunkflash_list=self.webpackChunkflash_list||[]).push([[706],{5680:(e,t,n)=>{n.d(t,{xA:()=>c,yg:()=>h});var a=n(6540);function i(e,t,n){return t in e?Object.defineProperty(e,t,{value:n,enumerable:!0,configurable:!0,writable:!0}):e[t]=n,e}function s(e,t){var n=Object.keys(e);if(Object.getOwnPropertySymbols){var a=Object.getOwnPropertySymbols(e);t&&(a=a.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),n.push.apply(n,a)}return n}function r(e){for(var t=1;t<arguments.length;t++){var n=null!=arguments[t]?arguments[t]:{};t%2?s(Object(n),!0).forEach((function(t){i(e,t,n[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(n)):s(Object(n)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(n,t))}))}return e}function o(e,t){if(null==e)return{};var n,a,i=function(e,t){if(null==e)return{};var n,a,i={},s=Object.keys(e);for(a=0;a<s.length;a++)n=s[a],t.indexOf(n)>=0||(i[n]=e[n]);return i}(e,t);if(Object.getOwnPropertySymbols){var s=Object.getOwnPropertySymbols(e);for(a=0;a<s.length;a++)n=s[a],t.indexOf(n)>=0||Object.prototype.propertyIsEnumerable.call(e,n)&&(i[n]=e[n])}return i}var l=a.createContext({}),d=function(e){var t=a.useContext(l),n=t;return e&&(n="function"==typeof e?e(t):r(r({},t),e)),n},c=function(e){var t=d(e.components);return a.createElement(l.Provider,{value:t},e.children)},u={inlineCode:"code",wrapper:function(e){var t=e.children;return a.createElement(a.Fragment,{},t)}},p=a.forwardRef((function(e,t){var n=e.components,i=e.mdxType,s=e.originalType,l=e.parentName,c=o(e,["components","mdxType","originalType","parentName"]),p=d(n),h=i,m=p["".concat(l,".").concat(h)]||p[h]||u[h]||s;return n?a.createElement(m,r(r({ref:t},c),{},{components:n})):a.createElement(m,r({ref:t},c))}));function h(e,t){var n=arguments,i=t&&t.mdxType;if("string"==typeof e||i){var s=n.length,r=new Array(s);r[0]=p;var o={};for(var l in t)hasOwnProperty.call(t,l)&&(o[l]=t[l]);o.originalType=e,o.mdxType="string"==typeof e?e:i,r[1]=o;for(var d=2;d<s;d++)r[d]=n[d];return a.createElement.apply(null,r)}return a.createElement.apply(null,n)}p.displayName="MDXCreateElement"},9594:(e,t,n)=>{n.r(t),n.d(t,{contentTitle:()=>l,default:()=>p,frontMatter:()=>o,metadata:()=>d,toc:()=>c});var a=n(8168),i=n(8587),s=(n(6540),n(5680)),r=["components"],o={id:"known-issues",title:"Known issues",slug:"/known-issues",sidebar_position:3},l="Known Issues",d={unversionedId:"known-issues",id:"known-issues",title:"Known issues",description:"FlashList and FlatList have very different internal. While the API is almost the same, the behaviour might be different in some cases due to a bug, limitation or missing implementation. In any case, if the issue is already listed here don't create a new one.",source:"@site/docs/known-issues.md",sourceDirName:".",slug:"/known-issues",permalink:"/flash-list/docs/known-issues",editUrl:"https://github.com/Shopify/flash-list/blob/main/documentation/docs/known-issues.md",tags:[],version:"current",lastUpdatedBy:"dependabot[bot]",lastUpdatedAt:1724949694,formattedLastUpdatedAt:"8/29/2024",sidebarPosition:3,frontMatter:{id:"known-issues",title:"Known issues",slug:"/known-issues",sidebar_position:3},sidebar:"autoSidebar",previous:{title:"Testing with Jest",permalink:"/flash-list/docs/testing"}},c=[{value:"1) FlashList&#39;s rendered size is not usable warning",id:"1-flashlists-rendered-size-is-not-usable-warning",children:[],level:3},{value:"2) <code>onEndReached</code> event doesn&#39;t have <code>distanceFromEnd</code>",id:"2-onendreached-event-doesnt-have-distancefromend",children:[],level:3},{value:"3) <code>renderItem</code> callback doesn&#39;t have all features",id:"3-renderitem-callback-doesnt-have-all-features",children:[],level:3},{value:"4) Web support is in beta",id:"4-web-support-is-in-beta",children:[],level:3},{value:"5) <code>react-native-windows/macos</code> support",id:"5-react-native-windowsmacos-support",children:[],level:3}],u={toc:c};function p(e){var t=e.components,n=(0,i.A)(e,r);return(0,s.yg)("wrapper",(0,a.A)({},u,n,{components:t,mdxType:"MDXLayout"}),(0,s.yg)("h1",{id:"known-issues"},"Known Issues"),(0,s.yg)("p",null,"FlashList and FlatList have very different internal. While the API is almost the same, the behaviour might be different in some cases due to a bug, limitation or missing implementation. In any case, if the issue is already listed here don't create a new one."),(0,s.yg)("h3",{id:"1-flashlists-rendered-size-is-not-usable-warning"},"1) FlashList's rendered size is not usable warning"),(0,s.yg)("p",null,(0,s.yg)("inlineCode",{parentName:"p"},"FlashList")," uses ",(0,s.yg)("a",{parentName:"p",href:"https://github.com/Flipkart/recyclerlistview"},"recyclerlistview")," to leverage its recycling capability. ",(0,s.yg)("inlineCode",{parentName:"p"},"recyclerlistview's")," default layout algorithm cannot work without a valid size. It needs to first measure itself and then decide how much to draw and reuse. So, make sure that the parent of the list mounts with a valid size (>=2px) and ",(0,s.yg)("inlineCode",{parentName:"p"},"FlashList")," will match the size of its parent. Please note that you cannot apply style directly to ",(0,s.yg)("inlineCode",{parentName:"p"},"FlashList")," so you may need to wrap it in a ",(0,s.yg)("inlineCode",{parentName:"p"},"View"),"."),(0,s.yg)("p",null,"Please note most lists do mount with deterministic sizes so make sure to check if you really need workarounds."),(0,s.yg)("h3",{id:"2-onendreached-event-doesnt-have-distancefromend"},"2) ",(0,s.yg)("inlineCode",{parentName:"h3"},"onEndReached")," event doesn't have ",(0,s.yg)("inlineCode",{parentName:"h3"},"distanceFromEnd")),(0,s.yg)("p",null,"This value is reported as 0. We don't have plans to implement this right now. Please provide feedback if this is important to you."),(0,s.yg)("h3",{id:"3-renderitem-callback-doesnt-have-all-features"},"3) ",(0,s.yg)("inlineCode",{parentName:"h3"},"renderItem")," callback doesn't have all features"),(0,s.yg)("p",null,"As of now we only provide relevant data and index. No plans to change this."),(0,s.yg)("h3",{id:"4-web-support-is-in-beta"},"4) Web support is in beta"),(0,s.yg)("ul",null,(0,s.yg)("li",{parentName:"ul"},"Layout is async so it's possible to see shift animations on list load."),(0,s.yg)("li",{parentName:"ul"},(0,s.yg)("inlineCode",{parentName:"li"},"onBlankArea")," event and ",(0,s.yg)("inlineCode",{parentName:"li"},"useBlankAreaTracker")," hook are not supported.")),(0,s.yg)("p",null,"Exercise caution and make sure all changes are tested on web as there could be some differences when compared to Android/iOS."),(0,s.yg)("h3",{id:"5-react-native-windowsmacos-support"},"5) ",(0,s.yg)("inlineCode",{parentName:"h3"},"react-native-windows/macos")," support"),(0,s.yg)("p",null,"FlashList will run in JS only mode on both Windows and macOS. We don't have plans to write native code or actively test on platforms other than Android, iOS and Web."))}p.isMDXComponent=!0}}]);