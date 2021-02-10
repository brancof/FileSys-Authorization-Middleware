package helloworld.resources;

import com.fasterxml.jackson.annotation.JsonCreator;
import com.fasterxml.jackson.annotation.JsonProperty;

import java.time.Duration;
import java.time.LocalDateTime;
import java.util.HashMap;
import java.util.Map;

import javax.ws.rs.GET;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.QueryParam;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;

@Path("/permition")
@Produces(MediaType.APPLICATION_JSON)
public class CodeResource {
    private String cod;
    private int num;
    private LocalDateTime dataLast;

    public CodeResource() {
        this.cod = "";
        this.num = 0;
        this.dataLast = null;
    }

    @GET
    public Response getCode() {
        if(this.cod.equals("")){
            return Response.status(403).build();
        }else return Response.ok(this.cod).build();
    }

    @POST
    @Path("/codigo")
    public Response add(Cod cm) {
        try {
            if(this.num < 3) {
                this.cod = cm.codigo;
                this.num++;
                this.dataLast = LocalDateTime.now();
                return Response.ok().build();
            }
            else{
                if( Duration.between(this.dataLast, LocalDateTime.now()).toMillis() > 5000){
                    this.cod = cm.codigo;
                    this.num = 1;
                    this.dataLast = LocalDateTime.now();
                    return Response.ok().build();
                }else{
                    return Response.status(403).build();
                }
            }
        }catch (Exception e){
           return Response.status(403).build();

        }
    }

    public static class Cod {
        @JsonProperty("codigo")
        public String codigo;
    }


}



