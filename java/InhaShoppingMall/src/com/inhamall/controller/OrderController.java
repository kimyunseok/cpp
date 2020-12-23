package com.inhamall.controller;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.inhamall.dao.OrderDao;
import com.inhamall.dao.ProductDao;
import com.inhamall.model.Order;
import com.inhamall.model.Product;

@WebServlet("/OrderController")
public class OrderController extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private static String ORDER = "order.jsp";
    private static String LIST_ORDER = "order_list.jsp";
    private static String ADMIN = "admin.jsp";
    private static String MAIN = "index.jsp";
    private static String ADMIN_LIST_ORDER = "adminOrderList.jsp";
    
    private OrderDao dao;
    private ProductDao pdao;

    public OrderController() {
        super();
        dao = new OrderDao();
        pdao = new ProductDao();
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    	request.setCharacterEncoding("UTF-8");
    	response.setContentType("text/html;charset=UTF-8");
    	
        String forward="";
        String action = request.getParameter("action");
        
        if (action.equalsIgnoreCase("delete")){
            int orderidx = Integer.parseInt(request.getParameter("orderidx"));
            dao.deleteOrder(orderidx);
            forward = ADMIN_LIST_ORDER;
            request.setAttribute("orders", dao.getAllOrders());    
            
        } else if (action.equalsIgnoreCase("listOrder")){
        	String userid = request.getParameter("id");
            forward = LIST_ORDER;
            List<Order> orders = dao.getOrdersByUserId(userid);
            List<Product> products = new ArrayList<Product>();
            for(int i = 0; i < orders.size(); i++) {
            	products.add(pdao.getProductByIdx(orders.get(i).getProductidx()));
            }
            
            request.setAttribute("orders", orders);
            request.setAttribute("products", products);
        }  else if (action.equalsIgnoreCase("order")){
            forward = ORDER;
            int productidx = Integer.parseInt(request.getParameter("productidx"));
            Product product = pdao.getProductByIdx(productidx);	
            request.setAttribute("product", product);
        } else if (action.equalsIgnoreCase("adminlistOrder")){
            forward = ADMIN_LIST_ORDER;
            List<Order> orders = dao.getAllOrders();
            List<Product> products = new ArrayList<Product>();
            for(int i = 0; i < orders.size(); i++) {
            	products.add(pdao.getProductByIdx(orders.get(i).getProductidx()));
            }
            request.setAttribute("products", products);
            request.setAttribute("orders", orders);
        } else {
            forward = MAIN;
        }
        
        RequestDispatcher view = request.getRequestDispatcher(forward);
        view.forward(request, response);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    	request.setCharacterEncoding("UTF-8");
    	response.setContentType("text/html;charset=UTF-8");
    	
    	Order order = new Order();
    	
    	order.setUserid(request.getParameter("userid"));
    	order.setProductidx(Integer.parseInt(request.getParameter("productidx")));
    	order.setQty(Integer.parseInt(request.getParameter("qty")));
    	order.setMemo(request.getParameter("memo"));
        
        String orderIdx = request.getParameter("orderidx");
        if(orderIdx == null || orderIdx.isEmpty())
        {
            dao.addOrder(order);
        }
        
        RequestDispatcher view = request.getRequestDispatcher(MAIN);
        request.setAttribute("orders", dao.getOrdersByUserId(order.getUserid()));
        view.forward(request, response);
    }
}