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

import com.inhamall.dao.BasketDao;
import com.inhamall.dao.ProductDao;
import com.inhamall.model.Basket;
import com.inhamall.model.Product;

@WebServlet("/BasketController")
public class BasketController extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private static String ORDER = "order.jsp";
    private static String BASKET = "basket.jsp";
    private static String MAIN = "index.jsp";
    
    private BasketDao dao;
    private ProductDao pdao;

    public BasketController() {
        super();
        dao = new BasketDao();
        pdao = new ProductDao();
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    	request.setCharacterEncoding("UTF-8");
    	response.setContentType("text/html;charset=UTF-8");
    	
        String forward="";
        String action = request.getParameter("action");
        
        if (action.equalsIgnoreCase("delete")){
            int basketidx = Integer.parseInt(request.getParameter("basketidx"));
            String userid = dao.getBasketByIdx(basketidx).getUserid();
            dao.deleteBasket(basketidx);
            forward = BASKET;
            request.setAttribute("baskets", dao.getBasketsByUserId(userid));    
        } else if (action.equalsIgnoreCase("basket")){
        	String userid = request.getParameter("id");
            forward = BASKET;
            List<Basket> baskets = dao.getBasketsByUserId(userid);
            List<Product> products = new ArrayList<Product>();
            for(int i = 0; i < baskets.size(); i++) {
            	products.add(pdao.getProductByIdx(baskets.get(i).getProductidx()));
            }
            
            request.setAttribute("baskets", baskets);
            request.setAttribute("products", products);
        }  else if (action.equalsIgnoreCase("order")){
            forward = ORDER;
            int productidx = Integer.parseInt(request.getParameter("productidx"));
            int qty = Integer.parseInt(request.getParameter("qty"));
            request.setAttribute("productidx", productidx);
            request.setAttribute("qty", qty);
        } else {
            forward = MAIN;
        }
        
        RequestDispatcher view = request.getRequestDispatcher(forward);
        view.forward(request, response);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    	request.setCharacterEncoding("UTF-8");
    	response.setContentType("text/html;charset=UTF-8");
    	
    	Basket basket = new Basket();
    	
    	basket.setUserid(request.getParameter("userid"));
    	basket.setProductidx(Integer.parseInt(request.getParameter("productidx")));
    	basket.setQty(Integer.parseInt(request.getParameter("qty")));
        
        String basketIdx = request.getParameter("basketidx");
        if(basketIdx == null || basketIdx.isEmpty())
        {
            dao.addBasket(basket);
        }
        
        RequestDispatcher view = request.getRequestDispatcher(MAIN);
        request.setAttribute("baskets", dao.getBasketsByUserId(basket.getUserid()));
        view.forward(request, response);
    }
}