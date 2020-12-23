<%@ page language="java" contentType="text/html; charset=utf-8"
	pageEncoding="utf-8"%>
<!DOCTYPE html>
<html>
<head>
<link type="text/css" rel="stylesheet" href="style.css">
<title>관리자 페이지</title>
</head>
<body>
	<center>
	<form style="padding: 100px">
	<h1>관리자 페이지</h1>
	<a href="OrderController?action=adminlistOrder">주문 목록 확인</a><br><br>
	<a href="ProductController?action=listProduct">상품 리스트(수정 / 추가 및 삭제)</a><br><br>
	<a href="UserController?action=listUser">회원 리스트(수정 및 삭제)</a></p>
	<input type="button" onclick="location.href='index.jsp'" value="홈화면" style="border-radius: 5px; height: 75px; width: 200px; background-color: black; color: white; margin-right: 30px; font-size: 18px;">
	
	</form>
	</center>

	<hr>

	<footer>
		<%@include file="layout/bottom.jsp"%>
	</footer>
</html>