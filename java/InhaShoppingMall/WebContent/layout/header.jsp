<%@page import="com.inhamall.model.User"%>
<%@page import="com.inhamall.dao.UserDao"%>
<%@ page language="java" contentType="text/html; charset=utf-8"
	pageEncoding="utf-8"%>
<!DOCTYPE html>
<html>
<head>
<link type="text/css" rel="stylesheet" href="style.css">
<title>InHa Mall 2020</title>
</head>
<body>

<%
		String id="";

			id=(String)session.getAttribute("id");
			
			if(id==null||id.equals("")){
				%>
	<a href="https://www.inha.ac.kr/kr/970/subview.do" target="_blank"><img src="image/q.jpg"
	width="30px" height="50px" style="float: right;"> </a>
	
	<input type="button" value="로그인" onclick="location.href='login.jsp'" class="HeaderLR"
		style="border-radius: 5px; height: 50px; width: 200px; 
		background-color: black; color: white; margin-right: 30px; font-size: 18px; font: bold;"/> &nbsp;&nbsp;&nbsp;
	
	<input type="button" value="회원가입" onclick="location.href='signup.jsp'" class="HeaderLR"
		style="border-radius: 5px; height: 50px; width: 200px; 
		background-color: black; color: white; margin-right: 30px; font-size: 18px; font: bold;"/> &nbsp;&nbsp;&nbsp;
	
	<input type="button" value="아이디/ 비밀번호 찾기" onclick="location.href='findIDPW.jsp'" class="HeaderLR"
		style="border-radius: 5px; height: 50px; width: 200px; 
		background-color: black; color: white; margin-right: 30px; font-size: 18px; font: bold;"/>
	<p>
		<a href="index.jsp"><img src="image/Logo.png"></a>
	</p>
<%
			} else {
				UserDao dao = new UserDao();
				User user = dao.getUserById(id);
				String level = "";
				level = user.getUsertype() == 0? "일반 회원" : user.getUsertype() == 1? "Lv.1 실버 회원" : user.getUsertype() == 2? "◆ 골드 회원" :
					user.getUsertype() == 3? "♣ 플래티넘 회원" : user.getUsertype() == 4? "★ VIP 회원" : "※ 관리자";
				%>

<a href="https://www.inha.ac.kr/kr/970/subview.do" target="_blank"><img src="image/q.jpg"
	width="30px" height="50px" style="float: right;"> <a
	href="BasketController?action=basket&id=<%=id%>"><img src="image/shoping_cart.jpg"
		width="40px" height="50px" style="float: right;"></a> <br>
		<h1><%=level + "<h1><h2>" + user.getUsername() + " 님 환영합니다." %></h2> <br><br>
		
		<input type="button" value="로그아웃" onclick="location.href='logoutGo.jsp'" class="HeaderMenu"
		style="border-radius: 5px; height: 50px; width: 200px; font-size: 15px;
		background-color: black; color: white; margin-right: 30px; font-size: 18px; font: bold;"/> &nbsp;&nbsp;&nbsp;
		
		<input type="button" value="주문 내역 확인" onclick="location.href='OrderController?action=listOrder&id=<%=user.getId() %>'" class="HeaderMenu"
		style="border-radius: 5px; height: 50px; width: 200px; 
		background-color: black; color: white; margin-right: 30px; font-size: 18px; font: bold;"/> &nbsp;&nbsp;&nbsp;
		
		<input type="button" value="회원정보 수정" onclick="location.href='UserController?action=edit&useridx=<%=user.getUseridx() %>'" class="HeaderMenu"
		style="border-radius: 5px; height: 50px; width: 200px; 
		background-color: black; color: white; margin-right: 30px; font-size: 18px; font: bold;"/> &nbsp;&nbsp;&nbsp;

		<%if(user.getUsertype() == 5) { %>
		<input type="button" value="관리자 페이지" class="HeaderMenu" onclick="location.href='admin.jsp'"
		style="border-radius: 5px; height: 50px; width: 200px; 
		background-color:blue; color: white; margin-right: 30px; font-size: 18px; font: bold;"/>
		<%} %>


	<p>
		<a href="index.jsp"><img src="image/Logo.png"></a>
	</p>
<%
			}
	%>
</body>
</html>