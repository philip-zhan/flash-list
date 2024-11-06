"use strict";(self.webpackChunkflash_list=self.webpackChunkflash_list||[]).push([[118],{5680:(e,t,n)=>{n.d(t,{xA:()=>c,yg:()=>d});var r=n(6540);function i(e,t,n){return t in e?Object.defineProperty(e,t,{value:n,enumerable:!0,configurable:!0,writable:!0}):e[t]=n,e}function a(e,t){var n=Object.keys(e);if(Object.getOwnPropertySymbols){var r=Object.getOwnPropertySymbols(e);t&&(r=r.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),n.push.apply(n,r)}return n}function s(e){for(var t=1;t<arguments.length;t++){var n=null!=arguments[t]?arguments[t]:{};t%2?a(Object(n),!0).forEach((function(t){i(e,t,n[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(n)):a(Object(n)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(n,t))}))}return e}function o(e,t){if(null==e)return{};var n,r,i=function(e,t){if(null==e)return{};var n,r,i={},a=Object.keys(e);for(r=0;r<a.length;r++)n=a[r],t.indexOf(n)>=0||(i[n]=e[n]);return i}(e,t);if(Object.getOwnPropertySymbols){var a=Object.getOwnPropertySymbols(e);for(r=0;r<a.length;r++)n=a[r],t.indexOf(n)>=0||Object.prototype.propertyIsEnumerable.call(e,n)&&(i[n]=e[n])}return i}var l=r.createContext({}),p=function(e){var t=r.useContext(l),n=t;return e&&(n="function"==typeof e?e(t):s(s({},t),e)),n},c=function(e){var t=p(e.components);return r.createElement(l.Provider,{value:t},e.children)},u={inlineCode:"code",wrapper:function(e){var t=e.children;return r.createElement(r.Fragment,{},t)}},g=r.forwardRef((function(e,t){var n=e.components,i=e.mdxType,a=e.originalType,l=e.parentName,c=o(e,["components","mdxType","originalType","parentName"]),g=p(n),d=i,m=g["".concat(l,".").concat(d)]||g[d]||u[d]||a;return n?r.createElement(m,s(s({ref:t},c),{},{components:n})):r.createElement(m,s({ref:t},c))}));function d(e,t){var n=arguments,i=t&&t.mdxType;if("string"==typeof e||i){var a=n.length,s=new Array(a);s[0]=g;var o={};for(var l in t)hasOwnProperty.call(t,l)&&(o[l]=t[l]);o.originalType=e,o.mdxType="string"==typeof e?e:i,s[1]=o;for(var p=2;p<a;p++)s[p]=n[p];return r.createElement.apply(null,s)}return r.createElement.apply(null,n)}g.displayName="MDXCreateElement"},1882:(e,t,n)=>{n.r(t),n.d(t,{contentTitle:()=>l,default:()=>g,frontMatter:()=>o,metadata:()=>p,toc:()=>c});var r=n(8168),i=n(8587),a=(n(6540),n(5680)),s=["components"],o={id:"testing",title:"Testing with Jest",slug:"/testing"},l=void 0,p={unversionedId:"guides/testing",id:"guides/testing",title:"Testing with Jest",description:"Since FlashList does not immediately render but waits for the size of the underlying ScrollView (unless you specify estimatedListSize), we need to mock triggering onLayout event.",source:"@site/docs/guides/testing.md",sourceDirName:"guides",slug:"/testing",permalink:"/flash-list/docs/testing",editUrl:"https://github.com/Shopify/flash-list/blob/main/documentation/docs/guides/testing.md",tags:[],version:"current",lastUpdatedBy:"David Cort\xe9s",lastUpdatedAt:1730912720,formattedLastUpdatedAt:"11/6/2024",frontMatter:{id:"testing",title:"Testing with Jest",slug:"/testing"},sidebar:"autoSidebar",previous:{title:"SectionList",permalink:"/flash-list/docs/guides/section-list"},next:{title:"Known issues",permalink:"/flash-list/docs/known-issues"}},c=[{value:"Setup",id:"setup",children:[],level:2},{value:"Example",id:"example",children:[],level:2}],u={toc:c};function g(e){var t=e.components,n=(0,i.A)(e,s);return(0,a.yg)("wrapper",(0,r.A)({},u,n,{components:t,mdxType:"MDXLayout"}),(0,a.yg)("p",null,"Since ",(0,a.yg)("inlineCode",{parentName:"p"},"FlashList")," does not immediately render but waits for the size of the underlying ",(0,a.yg)("inlineCode",{parentName:"p"},"ScrollView")," (unless you specify ",(0,a.yg)("a",{parentName:"p",href:"usage#estimatedlistsize"},(0,a.yg)("inlineCode",{parentName:"a"},"estimatedListSize")),"), we need to mock triggering ",(0,a.yg)("inlineCode",{parentName:"p"},"onLayout")," event."),(0,a.yg)("h2",{id:"setup"},"Setup"),(0,a.yg)("p",null,"Add the following line to your ",(0,a.yg)("inlineCode",{parentName:"p"},"jest-setup.js")," file:"),(0,a.yg)("pre",null,(0,a.yg)("code",{parentName:"pre",className:"language-js"},'require("@shopify/flash-list/jestSetup");\n')),(0,a.yg)("p",null,"To be sure, check if your jest.config.js file contains:"),(0,a.yg)("pre",null,(0,a.yg)("code",{parentName:"pre"},"...\npreset: 'react-native',\nsetupFiles: ['./jest-setup.js'],\n...\n")),(0,a.yg)("h2",{id:"example"},"Example"),(0,a.yg)("p",null,"Here is an example of using ",(0,a.yg)("a",{parentName:"p",href:"https://callstack.github.io/react-native-testing-library/"},(0,a.yg)("inlineCode",{parentName:"a"},"@testing-library/react-native")),":"),(0,a.yg)("pre",null,(0,a.yg)("code",{parentName:"pre",className:"language-tsx"},'import React from "react";\nimport { render } from "@testing-library/react-native";\n\ndescribe("MyFlashListComponent", () => {\n  it("renders items", () => {\n    const { getByText } = render(<MyFlashListComponent />);\n    const element = getByText("Title of one of the items");\n    // Do something with element ...\n  });\n});\n')))}g.isMDXComponent=!0}}]);