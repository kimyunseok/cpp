package com.inhamall.controller;

import java.io.IOException;
import java.util.List;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.inhamall.dao.UserDao;
import com.inhamall.model.User;

@WebServlet("/UserController")
public class UserController extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private static String EDIT = "userEdit.jsp";
    private static String ADMIN_EDIT = "adminuserEdit.jsp";
    private static String LIST_USER = "adminuserList.jsp";
    private static String MAIN = "index.jsp";
    
    private UserDao dao;

    public UserController() {
        super();
        dao = new UserDao();
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    	request.setCharacterEncoding("UTF-8");
    	response.setContentType("text/html;charset=UTF-8");
    	
        String forward="";
        String action = request.getParameter("action");
        
        if (action.equalsIgnoreCase("delete")){
            int useridx = Integer.parseInt(request.getParameter("useridx"));
            dao.deleteUser(useridx);
            forward = LIST_USER;
            request.setAttribute("users", dao.getAllUsers()); 
            
        } else if (action.equalsIgnoreCase("edit")){
            forward = EDIT;
            int userIdx = Integer.parseInt(request.getParameter("useridx"));
            User user = dao.getUserByIdx(userIdx);
            request.setAttribute("user", user);
            
        } else if (action.equalsIgnoreCase("adminedit")){
            forward = ADMIN_EDIT;
            int userIdx = Integer.parseInt(request.getParameter("useridx"));
            User user = dao.getUserByIdx(userIdx);
            request.setAttribute("user", user);
            
        } else if (action.equalsIgnoreCase("listUser")){
            forward = LIST_USER;
            List<User> users = dao.getAllUsers();
            request.setAttribute("users", users);
            
        } else if("insert".equals(action)){
        	forward = "signup.jsp";
        }else {
            forward = MAIN;
        }

        RequestDispatcher view = request.getRequestDispatcher(forward);
        view.forward(request, response);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    	request.setCharacterEncoding("UTF-8");
    	response.setContentType("text/html;charset=UTF-8");
    	
    	User user = new User();
    	
    	if(request.getParameter("usertype") == null) {
    		user.setUsertype(0);
    	} else {
    		user.setUsertype(Integer.parseInt(request.getParameter("usertype")));
    	}
    	
    	user.setId(request.getParameter("id"));
    	user.setPassword(request.getParameter("password"));
    	user.setUsername(request.getParameter("name"));
        user.setDob(request.getParameter("dob"));
        user.setSex(request.getParameter("sex"));
        user.setContact(request.getParameter("contact"));
        user.setAddress(request.getParameter("address"));
        user.setEmail(request.getParameter("email"));
        
        String userIdx = request.getParameter("useridx");
        if(userIdx == null || userIdx.isEmpty())
        {
            dao.addUser(user);
        }
        else
        {
            user.setUseridx(Integer.parseInt(userIdx));
            dao.updateUser(user);
        }
        RequestDispatcher view = request.getRequestDispatcher(MAIN);
        request.setAttribute("users", dao.getAllUsers());
        view.forward(request, response);
    }
}