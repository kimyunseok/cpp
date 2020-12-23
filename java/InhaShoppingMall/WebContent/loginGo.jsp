<%@page import="com.inhamall.dao.UserDao"%>
<%@page import="com.inhamall.model.User"%>
<%@ page language="java" contentType="text/html; charset=utf-8"
	pageEncoding="utf-8"%>

<%@ page import="java.sql.*"%>

<%
	request.setCharacterEncoding("utf-8");
%>

<%
	String id = request.getParameter("id");
	String passwd = request.getParameter("passwd");
%>

<%
	UserDao dao = new UserDao();
	User user = dao.Login(id, passwd);
	String check = "";
	try {
		if(user != null) {
			%>
			<%
			session.setAttribute("id",id);
			if(user.getUsertype() == 5){
				%>
				<jsp:forward page="admin.jsp"/>
				<%
			 }else {
				 %>
					<jsp:forward page="index.jsp"/>
					<%
			 }
			
			
		} else { check="로그인에 실패했습니다.<br>아이디와 비밀번호를 확인해 보세요.";}
		
		
	} catch (Exception e) {
		e.printStackTrace();
	}

%>
<center>
<h2><%=check %></h2>
<img alt="" src="image/fail.png"> <br><br>

 <input type="button" onclick="location.href='index.jsp'" value="홈화면" style="border-radius: 5px; height: 75px; width: 200px; background-color: black; color: white; margin-right: 30px; font-size: 18px;">
 &nbsp;&nbsp;&nbsp;
 
 <input type="button" onclick="location.href='login.jsp'" value="로그인화면" style="border-radius: 5px; height: 75px; width: 200px; background-color: black; color: white; margin-right: 30px; font-size: 18px;">
  &nbsp;&nbsp;&nbsp;
  
 <input type="button" onclick="location.href='findIDPW.jsp'" value="아이디/ 비밀번호 찾기" style="border-radius: 5px; height: 75px; width: 200px; background-color: black; color: white; margin-right: 30px; font-size: 18px;">
 </center>